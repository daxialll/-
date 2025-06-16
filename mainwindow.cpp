#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QTableWidgetItem>
#include <QRegularExpression>
#include <QMessageBox>
#include <QDebug>

const int L = 40;  // 每页行数

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), u(new Ui::MainWindow) {
    u->setupUi(this);

    loadBooks("books");  // 你的文件夹

    u->tableWidget->setColumnCount(5);
    u->tableWidget->setHorizontalHeaderLabels({"序号", "关键词", "页码", "章节", "书名"});

    connect(u->searchButton, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);
    connect(u->tableWidget, &QTableWidget::cellClicked, this, &MainWindow::on_tableWidget_cellClicked);

    qDebug() << "当前程序运行目录:" << QDir::currentPath();
}

MainWindow::~MainWindow() {
    delete u;
}

void MainWindow::loadBooks(const QString& f) {
    QDir d(f);
    if (!d.exists()) {
        QMessageBox::warning(this, "提示", f + " 文件夹不存在！");
        return;
    }

    QStringList fs = d.entryList(QStringList() << "*.txt", QDir::Files);

    for (const QString& fn : fs) {
        QFile file(d.filePath(fn));
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "打开文件失败", fn + " 无法打开");
            continue;
        }

        QTextStream in(&file);

        QStringList ls;
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty())
                ls.append(line);
        }
        QString bn = fn.left(fn.lastIndexOf('.'));
        bn.replace('_', ' ');

        t[bn] = ls;
        file.close();
    }
}

QVector<R> MainWindow::searchKeyword(const QString& k) {
    QVector<R> res;
    QRegularExpression re("^CHAPTER\\s+(\\d+)", QRegularExpression::CaseInsensitiveOption);

    int cnt = 1;
    for (auto it = t.constBegin(); it != t.constEnd(); ++it) {
        const QString& b = it.key();
        const QStringList& ls = it.value();

        int ch = 0;
        for (int i = 0; i < ls.size(); ++i) {
            QRegularExpressionMatch m = re.match(ls[i]);
            if (m.hasMatch()) {
                ch = m.captured(1).toInt();
            }

            if (ls[i].contains(k, Qt::CaseInsensitive)) {
                int p = i / L + 1;
                R r{cnt++, k, p, ch, b, i};
                res.append(r);
            }
        }
    }
    return res;
}

void MainWindow::on_searchButton_clicked() {
    QString k = u->lineEdit->text().trimmed();
    if (k.isEmpty()) {
        QMessageBox::information(this, "提示", "请输入关键词");
        return;
    }

    s = searchKeyword(k);

    u->tableWidget->setRowCount(s.size());
    for (int i = 0; i < s.size(); ++i) {
        const R& r = s[i];
        u->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(r.i)));
        u->tableWidget->setItem(i, 1, new QTableWidgetItem(r.k));
        u->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(r.p)));
        u->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(r.c)));
        u->tableWidget->setItem(i, 4, new QTableWidgetItem(r.b));
    }
}

QString MainWindow::getContext(const R& r) {
    const QStringList& ls = t[r.b];
    QStringList cx;

    int p = r.l;
    if (p - 1 >= 0) cx << ls[p - 1];
    cx << ls[p];
    if (p + 1 < ls.size()) cx << ls[p + 1];

    return cx.join("\n\n");
}

void MainWindow::on_tableWidget_cellClicked(int row, int /*col*/) {
    if (row < 0 || row >= s.size()) return;

    QString cx = getContext(s[row]);
    u->textEdit->setPlainText(cx);
}
