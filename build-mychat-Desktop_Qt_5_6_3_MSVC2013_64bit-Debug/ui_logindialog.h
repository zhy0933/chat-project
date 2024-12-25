/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QLabel *user_label;
    QLineEdit *user_lineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *pass_label;
    QLineEdit *pass_lineEdit;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QLabel *forget_label;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *login_btn;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *reg_btn;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->resize(300, 500);
        LoginDialog->setMinimumSize(QSize(300, 500));
        LoginDialog->setMaximumSize(QSize(300, 500));
        verticalLayout_2 = new QVBoxLayout(LoginDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget = new QWidget(LoginDialog);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/res/ice.png")));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        verticalLayout_2->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        user_label = new QLabel(LoginDialog);
        user_label->setObjectName(QStringLiteral("user_label"));
        user_label->setMinimumSize(QSize(0, 25));
        user_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(user_label);

        user_lineEdit = new QLineEdit(LoginDialog);
        user_lineEdit->setObjectName(QStringLiteral("user_lineEdit"));
        user_lineEdit->setMinimumSize(QSize(0, 25));
        user_lineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(user_lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pass_label = new QLabel(LoginDialog);
        pass_label->setObjectName(QStringLiteral("pass_label"));
        pass_label->setMinimumSize(QSize(0, 25));
        pass_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(pass_label);

        pass_lineEdit = new QLineEdit(LoginDialog);
        pass_lineEdit->setObjectName(QStringLiteral("pass_lineEdit"));
        pass_lineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(pass_lineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        forget_label = new QLabel(LoginDialog);
        forget_label->setObjectName(QStringLiteral("forget_label"));
        forget_label->setMinimumSize(QSize(0, 25));
        forget_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(forget_label);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        login_btn = new QPushButton(LoginDialog);
        login_btn->setObjectName(QStringLiteral("login_btn"));
        login_btn->setMinimumSize(QSize(100, 30));

        horizontalLayout_5->addWidget(login_btn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        reg_btn = new QPushButton(LoginDialog);
        reg_btn->setObjectName(QStringLiteral("reg_btn"));
        reg_btn->setMinimumSize(QSize(100, 30));

        horizontalLayout_6->addWidget(reg_btn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_4);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Dialog", Q_NULLPTR));
        label->setText(QString());
        user_label->setText(QApplication::translate("LoginDialog", "\347\224\250\346\210\267\357\274\232", Q_NULLPTR));
        pass_label->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        forget_label->setText(QApplication::translate("LoginDialog", "\345\277\230\350\256\260\345\257\206\347\240\201", Q_NULLPTR));
        login_btn->setText(QApplication::translate("LoginDialog", "\347\231\273\345\275\225", Q_NULLPTR));
        reg_btn->setText(QApplication::translate("LoginDialog", "\346\263\250\345\206\214", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
