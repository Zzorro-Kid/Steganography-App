/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.17
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tabInfo;
    QWidget *widget;
    QGridLayout *gridLayout;
    QPushButton *selectFileButton;
    QLineEdit *filePathLineEdit;
    QTextEdit *infoTextEdit;
    QPushButton *showInfoButton;
    QWidget *tabEmbed;
    QWidget *widget1;
    QGridLayout *gridLayout_2;
    QLineEdit *embedFilePathLineEdit;
    QPushButton *selectEmbedFileButton;
    QPushButton *embedButton;
    QLabel *statusLabel;
    QLabel *label;
    QTextEdit *messageTextEdit;
    QWidget *tabExtract;
    QWidget *widget2;
    QGridLayout *gridLayout_3;
    QLineEdit *extractFilePathLineEdit;
    QTextEdit *extractedMessageTextEdit;
    QPushButton *selectExtractFileButton;
    QPushButton *extractButton;
    QWidget *tabCheck;
    QWidget *widget3;
    QGridLayout *gridLayout_4;
    QLineEdit *checkFilePathLineEdit;
    QTextEdit *checkMessageTextEdit;
    QPushButton *selectCheckFileButton;
    QLabel *label_3;
    QPushButton *checkButton;
    QLabel *resultLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(60, 100, 501, 351));
        tabInfo = new QWidget();
        tabInfo->setObjectName(QString::fromUtf8("tabInfo"));
        widget = new QWidget(tabInfo);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(11, 11, 361, 263));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        selectFileButton = new QPushButton(widget);
        selectFileButton->setObjectName(QString::fromUtf8("selectFileButton"));

        gridLayout->addWidget(selectFileButton, 0, 0, 1, 1);

        filePathLineEdit = new QLineEdit(widget);
        filePathLineEdit->setObjectName(QString::fromUtf8("filePathLineEdit"));
        filePathLineEdit->setReadOnly(true);

        gridLayout->addWidget(filePathLineEdit, 1, 0, 1, 1);

        infoTextEdit = new QTextEdit(widget);
        infoTextEdit->setObjectName(QString::fromUtf8("infoTextEdit"));
        infoTextEdit->setReadOnly(false);

        gridLayout->addWidget(infoTextEdit, 2, 0, 1, 1);

        showInfoButton = new QPushButton(widget);
        showInfoButton->setObjectName(QString::fromUtf8("showInfoButton"));

        gridLayout->addWidget(showInfoButton, 2, 1, 1, 1);

        tabWidget->addTab(tabInfo, QString());
        tabEmbed = new QWidget();
        tabEmbed->setObjectName(QString::fromUtf8("tabEmbed"));
        widget1 = new QWidget(tabEmbed);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(10, 10, 361, 291));
        gridLayout_2 = new QGridLayout(widget1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        embedFilePathLineEdit = new QLineEdit(widget1);
        embedFilePathLineEdit->setObjectName(QString::fromUtf8("embedFilePathLineEdit"));
        embedFilePathLineEdit->setReadOnly(true);

        gridLayout_2->addWidget(embedFilePathLineEdit, 0, 0, 1, 1);

        selectEmbedFileButton = new QPushButton(widget1);
        selectEmbedFileButton->setObjectName(QString::fromUtf8("selectEmbedFileButton"));

        gridLayout_2->addWidget(selectEmbedFileButton, 0, 1, 1, 1);

        embedButton = new QPushButton(widget1);
        embedButton->setObjectName(QString::fromUtf8("embedButton"));

        gridLayout_2->addWidget(embedButton, 1, 0, 1, 1);

        statusLabel = new QLabel(widget1);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));

        gridLayout_2->addWidget(statusLabel, 1, 1, 1, 1);

        label = new QLabel(widget1);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 2, 0, 1, 1);

        messageTextEdit = new QTextEdit(widget1);
        messageTextEdit->setObjectName(QString::fromUtf8("messageTextEdit"));

        gridLayout_2->addWidget(messageTextEdit, 3, 0, 1, 1);

        tabWidget->addTab(tabEmbed, QString());
        tabExtract = new QWidget();
        tabExtract->setObjectName(QString::fromUtf8("tabExtract"));
        widget2 = new QWidget(tabExtract);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(10, 10, 406, 107));
        gridLayout_3 = new QGridLayout(widget2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        extractFilePathLineEdit = new QLineEdit(widget2);
        extractFilePathLineEdit->setObjectName(QString::fromUtf8("extractFilePathLineEdit"));
        extractFilePathLineEdit->setReadOnly(true);

        gridLayout_3->addWidget(extractFilePathLineEdit, 0, 0, 1, 1);

        extractedMessageTextEdit = new QTextEdit(widget2);
        extractedMessageTextEdit->setObjectName(QString::fromUtf8("extractedMessageTextEdit"));
        extractedMessageTextEdit->setTabChangesFocus(false);

        gridLayout_3->addWidget(extractedMessageTextEdit, 0, 1, 2, 1);

        selectExtractFileButton = new QPushButton(widget2);
        selectExtractFileButton->setObjectName(QString::fromUtf8("selectExtractFileButton"));

        gridLayout_3->addWidget(selectExtractFileButton, 1, 0, 1, 1);

        extractButton = new QPushButton(widget2);
        extractButton->setObjectName(QString::fromUtf8("extractButton"));

        gridLayout_3->addWidget(extractButton, 2, 0, 1, 1);

        tabWidget->addTab(tabExtract, QString());
        tabCheck = new QWidget();
        tabCheck->setObjectName(QString::fromUtf8("tabCheck"));
        widget3 = new QWidget(tabCheck);
        widget3->setObjectName(QString::fromUtf8("widget3"));
        widget3->setGeometry(QRect(10, 10, 406, 134));
        gridLayout_4 = new QGridLayout(widget3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        checkFilePathLineEdit = new QLineEdit(widget3);
        checkFilePathLineEdit->setObjectName(QString::fromUtf8("checkFilePathLineEdit"));
        checkFilePathLineEdit->setReadOnly(true);

        gridLayout_4->addWidget(checkFilePathLineEdit, 0, 0, 1, 1);

        checkMessageTextEdit = new QTextEdit(widget3);
        checkMessageTextEdit->setObjectName(QString::fromUtf8("checkMessageTextEdit"));

        gridLayout_4->addWidget(checkMessageTextEdit, 0, 1, 2, 1);

        selectCheckFileButton = new QPushButton(widget3);
        selectCheckFileButton->setObjectName(QString::fromUtf8("selectCheckFileButton"));

        gridLayout_4->addWidget(selectCheckFileButton, 1, 0, 1, 1);

        label_3 = new QLabel(widget3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_4->addWidget(label_3, 2, 0, 1, 1);

        checkButton = new QPushButton(widget3);
        checkButton->setObjectName(QString::fromUtf8("checkButton"));

        gridLayout_4->addWidget(checkButton, 2, 1, 1, 1);

        resultLabel = new QLabel(widget3);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));

        gridLayout_4->addWidget(resultLabel, 3, 0, 1, 1);

        tabWidget->addTab(tabCheck, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        selectFileButton->setText(QCoreApplication::translate("MainWindow", "Choose File", nullptr));
        filePathLineEdit->setText(QString());
        filePathLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "File Path (read-only)", nullptr));
        infoTextEdit->setDocumentTitle(QString());
        infoTextEdit->setMarkdown(QString());
        infoTextEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:7px; margin-bottom:7px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        infoTextEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Output Info", nullptr));
        showInfoButton->setText(QCoreApplication::translate("MainWindow", "Show Info", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabInfo), QCoreApplication::translate("MainWindow", "File Info", nullptr));
        embedFilePathLineEdit->setText(QString());
        embedFilePathLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "File Path (read-only)", nullptr));
        selectEmbedFileButton->setText(QCoreApplication::translate("MainWindow", "Choose File", nullptr));
        embedButton->setText(QCoreApplication::translate("MainWindow", "Embed message", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Status:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Embed message:", nullptr));
        messageTextEdit->setMarkdown(QString());
        messageTextEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:7px; margin-bottom:7px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        messageTextEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Message input field", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabEmbed), QCoreApplication::translate("MainWindow", "Embed Message", nullptr));
        extractFilePathLineEdit->setText(QString());
        extractFilePathLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "File Path (read-only)", nullptr));
        extractedMessageTextEdit->setDocumentTitle(QString());
        extractedMessageTextEdit->setMarkdown(QString());
        extractedMessageTextEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:7px; margin-bottom:7px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        extractedMessageTextEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Output of the extracted message", nullptr));
        selectExtractFileButton->setText(QCoreApplication::translate("MainWindow", "Choose File", nullptr));
        extractButton->setText(QCoreApplication::translate("MainWindow", "Extract message", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabExtract), QCoreApplication::translate("MainWindow", "Extract Message", nullptr));
        checkFilePathLineEdit->setText(QString());
        checkFilePathLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "File Path (read-only)", nullptr));
        checkMessageTextEdit->setMarkdown(QString());
        checkMessageTextEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:7px; margin-bottom:7px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        checkMessageTextEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Message input field", nullptr));
        selectCheckFileButton->setText(QCoreApplication::translate("MainWindow", "Choose File", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Message for verification:", nullptr));
        checkButton->setText(QCoreApplication::translate("MainWindow", "Check capacity", nullptr));
        resultLabel->setText(QCoreApplication::translate("MainWindow", "Check result:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabCheck), QCoreApplication::translate("MainWindow", "Check Capacity", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
