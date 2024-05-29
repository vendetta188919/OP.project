#include "PieChart.h"

#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>

#include <QLayout>

PieChart::PieChart(const std::vector<std::pair<QString, unsigned int> >& crVecValues, QWidget* pParent)
    : QDialog{pParent}
{
    QHBoxLayout* pMainLayout{new QHBoxLayout()};

    pMainLayout->addWidget(makePieChart(crVecValues));

    resize(600, 600);

    setWindowTitle(QString::fromLocal8Bit("Круговая диаграмма"));

    setLayout(pMainLayout);
}

QChartView * PieChart::makePieChart(const std::vector<std::pair<QString, unsigned int> >& crVecValues)
{
    QPieSeries* series = new QPieSeries();

    if(crVecValues.empty())
        series->append(QString::fromLocal8Bit("Пусто"), 1);

    for(const auto& pair : crVecValues)
        series->append(pair.first, pair.second);

    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

    for(auto slice : series->slices())
    {
        slice->setLabel(slice->label() + QString(" %1%").arg(100 * slice->percentage(), 0, 'f', 1));
        slice->setLabelBrush(QBrush(Qt::white));
    }

    QChart* chart = new QChart();

    chart->addSeries(series);

    QChartView* charView{new QChartView(chart)};
    charView->setRenderHint(QPainter::Antialiasing);

    return charView;
}
