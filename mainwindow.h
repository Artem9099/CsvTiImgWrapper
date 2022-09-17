#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QtCharts>
#include <QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <cmath>
#include <shlobj.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QFile file;
    QString fileTextCpy;
    QString newText;
    QStringList wordList;
    unsigned int posCounter;
    QList<float> dlTimeList;
    QList<float> dlPressureList;
    int iResolution;
    unsigned int iPointsTotal;
    unsigned int iPointsOut;
    QString sFilePath = "";
    // Configuration
    QChar cDelimiter = '\t';
    QString sDelimiter = "TAB";
    int iImageWidth = 50;
    int iImageHight = 50;
    QString sImageExtension = ".png";
    int iChartTheme = 0;
    int iCsvHandlingModeAfterConvert = 1;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnClose_clicked();

private:
    Ui::MainWindow *ui;
    void SetValueList(int resolution);
    void LoadFileContent();
    void DrawLineChart();
    void LoadConfigs();
    void SetTheme();
    void MoveCsvInSubfolder();
    void DeleteCsv();
};
#endif // MAINWINDOW_H
