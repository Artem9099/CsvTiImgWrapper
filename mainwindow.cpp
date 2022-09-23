#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoadConfigs();

    // Open file via doubleclick
    QStringList filenames = QCoreApplication::arguments();
    if (filenames.size() > 0) {
        for (int i=0; i < filenames.size(); i++) {
            sFilePath = filenames.at(i);
        }
        if(sFilePath.right(3).toLower() == "csv" || sFilePath.right(3).toLower() == "xml") {
            LoadFileContent();
            DrawLineChart();
        }
        else {
            qDebug() << "Ungültige Datei oder Datei nicht gefunden!";
        }
    }
//    // Test
//    sFilePath = "C:/Users/Artem_Starovojt/Desktop/test/test.xml";
//    LoadFileContent();
//    DrawLineChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetValueList(int resolution) {
    QTextStream textContent(&newText);
    double count = 0.0;
    dlTimeList.clear();
    dlPressureList.clear();
    wordList.clear();

    double x = double(posCounter) / 100 * double(resolution); //soviele punkte ausgeben
    double y = double(posCounter) - x;  //soviele punkte abziehen
    double z;
    if(y <= 0.0) {
        z = double(posCounter);
    }
    else {
        z = double(posCounter) / y;  //jeden z'ten punkt löschen
    }

    while(!textContent.atEnd()) {
        QString line = textContent.readLine();
        if(count <= z) {
            count += 1.0;
            if(cDelimiter != ',') {
                line.replace(",", ".");
            }
            wordList.append(line.split(cDelimiter));
            if(wordList.size() > 1) {
                dlTimeList << wordList[0].toFloat();
                dlPressureList << wordList[1].toFloat();
            }
            wordList.clear();
        }
        else {
            count = count - z + 1;
        }
    }
    iPointsOut = dlTimeList.count();
}

void MainWindow::LoadFileContent() {
    if(sFilePath.right(3).toLower() == "xml") {
        LoadXmlContent();
    }
    else {
        LoadCsvContent();
    }
}

void MainWindow::LoadCsvContent() {
    file.setFileName(sFilePath);
    fileTextCpy = "";
    newText = "";

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        fileTextCpy = file.readAll();
        QTextStream fileContent(&fileTextCpy);
        file.close();
        posCounter = 0;

        // Remove needles from string
        while(!fileContent.atEnd()) {
            QString line = fileContent.readLine().toLower();
            if(line.contains("0") && !line.contains("a") && !line.contains("b") && !line.contains("c") && !line.contains("d") && !line.contains("e")
                    && !line.contains("f") && !line.contains("g") && !line.contains("h") && !line.contains("i") && !line.contains("j")
                    && !line.contains("k") && !line.contains("l") && !line.contains("m") && !line.contains("n") && !line.contains("o")
                    && !line.contains("p") && !line.contains("q") && !line.contains("r") && !line.contains("s") && !line.contains("t")
                    && !line.contains("u") && !line.contains("v") && !line.contains("w") && !line.contains("x") && !line.contains("y")
                    && !line.contains("z")) {
                newText.append(line + "\n");
                posCounter++;
            }
        }
    }
    iPointsTotal = posCounter;
}

void MainWindow::LoadXmlContent() {
    QDomDocument measureXml;
    file.setFileName(sFilePath);
    newText = "";

    if (file.open(QIODevice::ReadOnly))
    {
        measureXml.setContent(&file);
        file.close();
        posCounter = 0;

        QDomElement root = measureXml.documentElement();
        QDomElement node = root.firstChild().toElement();

        if(node.tagName() == "MAIN.Druckrampe"){
            while(!node.isNull()){
                QDomNodeList axis = node.childNodes();
                QString x = axis.item(0).toElement().text();
                QString y = axis.item(1).toElement().text();

                newText.append(x).append(cDelimiter).append(y).append("\n");
                node = node.nextSibling().toElement();
                posCounter++;
            }
        }
        node = node.nextSibling().toElement();
    }
    iPointsTotal = posCounter;
    //qDebug() << newText;
}

void MainWindow::DrawLineChart() {
    QLineSeries *series = new QLineSeries();

    sFilePath.replace('\\', '/');
    QStringList splitPath = sFilePath.split('/');
    splitPath = splitPath[splitPath.count() - 1].split('.');
    sChartTitle = splitPath[0];

    series->setName(sChartTitle);

    SetValueList(100);

    unsigned int i = dlTimeList.count();

    series->clear();
    for (unsigned int var = 0; var < i; var++) {
        series->append(dlTimeList[var], dlPressureList[var]);
    }

    qDebug() << "Messpunkte insgesamt: " + QString::number(iPointsTotal) + " Messpunkte in der Grafik: " + QString::number(iPointsOut);

    QChart *chart = new QChart();

    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Messung");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setAnimationOptions(QChart::NoAnimation);

    QChartView *chartView = new QChartView();
    chartView->setChart(chart);
    QStringList imagePathSplit = sFilePath.split('.');
    QString imagePath = imagePathSplit[0] + sImageExtension;

    chartView->setMinimumWidth(iImageWidth);
    chartView->setMinimumHeight(iImageHight);
    chartView->setRenderHint(QPainter::Antialiasing);
    switch (iChartTheme) {
    case 0:
        chartView->chart()->setTheme(QChart::ChartThemeLight);
        break;
    case 1:
        chartView->chart()->setTheme(QChart::ChartThemeDark);
        break;
    case 2:
        chartView->chart()->setTheme(QChart::ChartThemeBlueCerulean);
        break;
    case 3:
        chartView->chart()->setTheme(QChart::ChartThemeBrownSand);
        break;
    case 4:
        chartView->chart()->setTheme(QChart::ChartThemeBlueNcs);
        break;
    case 5:
        chartView->chart()->setTheme(QChart::ChartThemeHighContrast);
        break;
    case 6:
        chartView->chart()->setTheme(QChart::ChartThemeBlueIcy);
        break;
    default:
        chartView->chart()->setTheme(QChart::ChartThemeLight);
        break;
    }

    chartView->grab().save(imagePath);

    switch (iDataFileHandlingModeAfterConvert) {
    case 1: // Move csv file in a subfolder
        MoveDataFileInSubfolder();
        break;
    case 2: // Remove the csv file
        DeleteDataFile();
        break;
    default:
        break;
    }

}

void MainWindow::on_btnClose_clicked()
{
    this->close();
}

void MainWindow::LoadConfigs() {
    QString cfgPath = QCoreApplication::applicationDirPath() + "/config.cfg";

    QString val;
    QFile file;
    file.setFileName(cfgPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());

    QJsonObject obj = doc.object();

    // Main parameter
    QJsonValue mainVal = obj.value(QString("delimiter"));
    sDelimiter = mainVal.toString();
    mainVal = obj.value(QString("imageWidth"));
    iImageWidth = mainVal.toInt();
    mainVal = obj.value(QString("imageHight"));
    iImageHight = mainVal.toInt();
    mainVal = obj.value(QString("imageExtension"));
    sImageExtension = mainVal.toString();
    mainVal = obj.value(QString("chartTheme"));
    iChartTheme = mainVal.toInt();
    mainVal = obj.value(QString("dataFileHandlingModeAfterConvert"));
    iDataFileHandlingModeAfterConvert = mainVal.toInt();

    if(sDelimiter.contains("TAB", Qt::CaseInsensitive)) {
        cDelimiter = '\t';
    }
    else if(sDelimiter.contains("COMMA", Qt::CaseInsensitive)) {
        cDelimiter = ',';
    }
    else {
        cDelimiter = ';';
    }
}

void MainWindow::MoveDataFileInSubfolder() {
    sFilePath.replace('\\', '/');
    QStringList splitPath = sFilePath.split('/');
    QString newPath = "";
    QString newFileDir = "";

    for (int var = 0; var < splitPath.count() - 1; var++) {
        newPath += (splitPath[var] + "/");
    }
    newFileDir = newPath + "DataFiles";
    newPath = newFileDir + "/" + splitPath[splitPath.count() - 1];

    QDir outputDir(newFileDir);
    if (!outputDir.exists()) {
        outputDir.mkdir(newFileDir);
    }
    if(QFileInfo::exists(newPath)) {
        QFile::remove(newPath);
    }

    QFile::rename(sFilePath, newPath);
}

void MainWindow::DeleteDataFile() {
    QStringList splitPath = sFilePath.split('.');
    QString imagePath = splitPath[0] + sImageExtension;

    if(QFileInfo::exists(imagePath)) {
        QFile::remove(sFilePath);
        if(!QFileInfo::exists(sFilePath)) {
            qDebug() << "Erfolgreich gelöscht: " + sFilePath;
        }
        else {
            qDebug() << "Fehler --> konnte nicht gelöscht werden: " + sFilePath;
        }
    }
}










