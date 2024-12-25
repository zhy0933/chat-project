/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_8;
    QLabel *err_tip;
    QHBoxLayout *horizontalLayout_2;
    QLabel *user_label;
    QLineEdit *user_lineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *email_label;
    QLineEdit *email_lineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *pass_label;
    QLineEdit *pass_lineEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *confirm_label;
    QLineEdit *confirm_lineEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *varify_label;
    QLineEdit *varify_lineEdit;
    QPushButton *get_code;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *confirm_btn;
    QPushButton *cancel_btn;
    QSpacerItem *verticalSpacer_3;
    QWidget *page_2;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName(QStringLiteral("RegisterDialog"));
        RegisterDialog->resize(300, 500);
        RegisterDialog->setMinimumSize(QSize(300, 500));
        RegisterDialog->setMaximumSize(QSize(300, 500));
        verticalLayout = new QVBoxLayout(RegisterDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        stackedWidget = new QStackedWidget(RegisterDialog);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        verticalLayout_4 = new QVBoxLayout(page);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_4->addItem(verticalSpacer);

        widget = new QWidget(page);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_8 = new QHBoxLayout(widget);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        err_tip = new QLabel(widget);
        err_tip->setObjectName(QStringLiteral("err_tip"));
        err_tip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_8->addWidget(err_tip);


        verticalLayout_4->addWidget(widget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        user_label = new QLabel(page);
        user_label->setObjectName(QStringLiteral("user_label"));
        user_label->setMinimumSize(QSize(0, 25));
        user_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(user_label);

        user_lineEdit = new QLineEdit(page);
        user_lineEdit->setObjectName(QStringLiteral("user_lineEdit"));
        user_lineEdit->setMinimumSize(QSize(0, 25));
        user_lineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(user_lineEdit);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        email_label = new QLabel(page);
        email_label->setObjectName(QStringLiteral("email_label"));
        email_label->setMinimumSize(QSize(0, 25));
        email_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(email_label);

        email_lineEdit = new QLineEdit(page);
        email_lineEdit->setObjectName(QStringLiteral("email_lineEdit"));
        email_lineEdit->setMinimumSize(QSize(0, 25));
        email_lineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(email_lineEdit);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pass_label = new QLabel(page);
        pass_label->setObjectName(QStringLiteral("pass_label"));
        pass_label->setMinimumSize(QSize(0, 25));
        pass_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(pass_label);

        pass_lineEdit = new QLineEdit(page);
        pass_lineEdit->setObjectName(QStringLiteral("pass_lineEdit"));
        pass_lineEdit->setMinimumSize(QSize(0, 25));
        pass_lineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(pass_lineEdit);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        confirm_label = new QLabel(page);
        confirm_label->setObjectName(QStringLiteral("confirm_label"));
        confirm_label->setMinimumSize(QSize(0, 25));
        confirm_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_5->addWidget(confirm_label);

        confirm_lineEdit = new QLineEdit(page);
        confirm_lineEdit->setObjectName(QStringLiteral("confirm_lineEdit"));
        confirm_lineEdit->setMinimumSize(QSize(0, 25));
        confirm_lineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_5->addWidget(confirm_lineEdit);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        varify_label = new QLabel(page);
        varify_label->setObjectName(QStringLiteral("varify_label"));
        varify_label->setMinimumSize(QSize(0, 25));
        varify_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(varify_label);

        varify_lineEdit = new QLineEdit(page);
        varify_lineEdit->setObjectName(QStringLiteral("varify_lineEdit"));
        varify_lineEdit->setMinimumSize(QSize(0, 25));
        varify_lineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(varify_lineEdit);

        get_code = new QPushButton(page);
        get_code->setObjectName(QStringLiteral("get_code"));
        get_code->setMinimumSize(QSize(0, 25));
        get_code->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(get_code);


        verticalLayout_4->addLayout(horizontalLayout_6);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_4->addItem(verticalSpacer_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        confirm_btn = new QPushButton(page);
        confirm_btn->setObjectName(QStringLiteral("confirm_btn"));
        confirm_btn->setMinimumSize(QSize(0, 25));
        confirm_btn->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_7->addWidget(confirm_btn);

        cancel_btn = new QPushButton(page);
        cancel_btn->setObjectName(QStringLiteral("cancel_btn"));
        cancel_btn->setMinimumSize(QSize(0, 25));
        cancel_btn->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_7->addWidget(cancel_btn);


        verticalLayout_4->addLayout(horizontalLayout_7);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_4->addItem(verticalSpacer_3);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        stackedWidget->addWidget(page_2);

        horizontalLayout->addWidget(stackedWidget);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(RegisterDialog);

        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QApplication::translate("RegisterDialog", "Dialog", Q_NULLPTR));
        err_tip->setText(QApplication::translate("RegisterDialog", "\351\224\231\350\257\257\346\217\220\347\244\272", Q_NULLPTR));
        user_label->setText(QApplication::translate("RegisterDialog", "\347\224\250\346\210\267\357\274\232", Q_NULLPTR));
        email_label->setText(QApplication::translate("RegisterDialog", "\351\202\256\347\256\261\357\274\232", Q_NULLPTR));
        pass_label->setText(QApplication::translate("RegisterDialog", "\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        confirm_label->setText(QApplication::translate("RegisterDialog", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        varify_label->setText(QApplication::translate("RegisterDialog", "\351\252\214\350\257\201\347\240\201\357\274\232", Q_NULLPTR));
        get_code->setText(QApplication::translate("RegisterDialog", "\350\216\267\345\217\226", Q_NULLPTR));
        confirm_btn->setText(QApplication::translate("RegisterDialog", "\347\241\256\350\256\244", Q_NULLPTR));
        cancel_btn->setText(QApplication::translate("RegisterDialog", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
