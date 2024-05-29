#pragma once

#include <string>
#include <vector>

#include <QChartView>
#include <QDialog>

class PieChart : public QDialog
{
    Q_OBJECT

public:
    explicit PieChart(const std::vector<std::pair<QString, unsigned int> >& crVecValues, QWidget* pParent = nullptr);

private:
    QChartView* makePieChart(const std::vector<std::pair<QString, unsigned int> >& crVecValues);
};
