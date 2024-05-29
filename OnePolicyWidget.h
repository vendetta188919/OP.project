#pragma once

#include <QDialog>
#include <QString>
#include <QHBoxLayout>
#include <QLabel>
#include <QVariant>
#include <QFont>

class OnePolicyWidget : public QDialog
{
public:
    explicit OnePolicyWidget(QWidget* pParent = nullptr);
    void makeDescription(const QVariant& crVar, const QString& crQstrTxt);

private:
    QHBoxLayout* makePairWidgets(QWidget* pLeftWidget, QWidget* pRightWidget) const;

    QLabel* makeDescriptionLbl(const QString& crQstrTxt) const;

    void AdjustHelpMenu();
};

