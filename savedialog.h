#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QObject>
#include <QDialog>

class QPushButton;
class QCheckBox;

class SaveDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SaveDialog(QWidget *parent = nullptr, QList<bool> enableList = QList<bool>(), QStringList options = QStringList(), QString title="");
    QList<bool> userChoice;

public slots:
    void saveClicked();
signals:

private:
    QPushButton *saveButton_;
    QPushButton *cancelButton_;
    QVector<QCheckBox*> checkboxes_;

};

#endif // SAVEDIALOG_H
