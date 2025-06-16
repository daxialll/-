#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QStringList>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct R {
    int i;          // 序号
    QString k;      // 关键词
    int p;          // 页码
    int c;          // 章节
    QString b;      // 书名
    int l;          // 关键词所在行号
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_searchButton_clicked();
    void on_tableWidget_cellClicked(int r, int c);

private:
    Ui::MainWindow *u;

    QMap<QString, QStringList> t;   // 书名->文本行列表
    QVector<R> s;                   // 搜索结果

    void loadBooks(const QString& f);
    QVector<R> searchKeyword(const QString& k);
    QString getContext(const R& r);
};

#endif // MAINWINDOW_H
