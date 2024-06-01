#ifndef NICKNAMEDIALOG_H
#define NICKNAMEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

class NicknameDialog : public QDialog {
    Q_OBJECT

public:
    NicknameDialog(QWidget* parent = nullptr) : QDialog(parent) {
        setWindowTitle("Ingresa tu Nickname");

        QVBoxLayout* layout = new QVBoxLayout(this);

        QLabel* label = new QLabel("Nickname:", this);
        layout->addWidget(label);

        nicknameEdit = new QLineEdit(this);
        layout->addWidget(nicknameEdit);

        QPushButton* okButton = new QPushButton("OK", this);
        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
        layout->addWidget(okButton);

        QPushButton* cancelButton = new QPushButton("Cancelar", this);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
        layout->addWidget(cancelButton);

        setLayout(layout);
    }

    QString getNickname() const {
        return nicknameEdit->text();
    }

private:
    QLineEdit* nicknameEdit;
};

#endif // NICKNAMEDIALOG_H
