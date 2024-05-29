#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

#include "TableView.h"

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

private slots:
    void onMakeNewPolicy();

    void onShowCurrentPolicy();
    void onRemove();
    void onFindMax();
    void onFindMin();
    void onShowMinValue(int iMinValue);
    void onShowMaxValue(int iMaxValue);
    void onFindTerm();
    void onFindArea();

    void onShowPie();

private:
    void initGui();
    void createConnections();
    bool callQuestionRemove(int iId);
    QHBoxLayout* makePairWidgets(QWidget* pLeftWidget = nullptr, QWidget* pRightWidget = nullptr);
    void showMsg(const QString& qstrMsg);
    void findFromValue(QLineEdit *pEdit, Keys key);


private:
    TableView* m_pView;
    QPushButton* m_pRemoveBtn;
    QPushButton* m_pCreateNewBtn;
    QPushButton* m_pSaveBtn;
    QPushButton* m_pShowOnePolicyBtn;
    QPushButton* m_pFindMinBtn;
    QPushButton* m_pFindMaxBtn;
    QPushButton* m_pFindTermBtn;
    QPushButton* m_pFindAreaBtn;
    QPushButton* m_pPieBtn;
    QLineEdit* m_pRemoveEdit;
    QLineEdit* m_pAreaEdit;
    QLineEdit* m_pTermEdit;
};
