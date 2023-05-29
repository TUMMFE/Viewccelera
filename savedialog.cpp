#include "savedialog.h"

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>

SaveDialog::SaveDialog(QWidget *parent, QList<bool> enableList, QStringList options, QString title)
    : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *label = new QLabel(tr("Select item to save"));
    layout->addWidget(label);

    for (int i = 0; i < options.size(); i++) {
        QCheckBox *box = new QCheckBox(options[i]);
        box->setEnabled(enableList[i]);
        layout->addWidget(box);
        checkboxes_.append(box);
    }

    QHBoxLayout *layoutButton = new QHBoxLayout;

    saveButton_ = new QPushButton(tr("Save"));
    cancelButton_ = new QPushButton(tr("Cancel"));
    layoutButton->addWidget(saveButton_);
    layoutButton->addWidget(cancelButton_);
    layout->addLayout(layoutButton);

    setLayout(layout);
    setWindowTitle(title);
    QIcon icon(":/Images/Save_256.png");
    setWindowIcon(icon);
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    connect(saveButton_, &QPushButton::clicked, this, &SaveDialog::saveClicked);
    connect(saveButton_, &QPushButton::clicked, this, &SaveDialog::accept);
    connect(cancelButton_, &QPushButton::clicked, this, &SaveDialog::reject);

}

void SaveDialog::saveClicked() {
    for (int i = 0; i<checkboxes_.size(); i++) {
        userChoice.append(checkboxes_[i]->checkState());
    }
    hide();
}
