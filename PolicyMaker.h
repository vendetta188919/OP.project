#pragma once

#include <vector>

#include <QDialog>
#include <QLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>

enum class Keys;

class PolicyMaker : public QDialog
{
    Q_OBJECT
public:
    explicit PolicyMaker(const std::vector<int>& crVecId, QWidget* pParent = nullptr);
signals:

    void sendData(std::vector<std::string>);

private slots:
    void onClose();
    void onCreate();

private:
    void initGui();
    void createConnections();
    QHBoxLayout* makePairWidgets(const QString &crQstrDescription, Keys key);
    QWidget* makeRedactorWidget(Keys key);
    QWidget* makeLineEdit(Keys key);

    std::string getRegExp(Keys key) const;
    std::vector<QString> getDescriptionsBox(Keys key) const;
    QWidget *makeComboBox(Keys key);

private:
    std::vector<std::pair<QWidget*, Keys> > m_vWidgets;
    QPushButton* m_pCreateBtn;
    QPushButton* m_pCancelBtn;
    std::vector<int> m_vIdPolicy;
};
