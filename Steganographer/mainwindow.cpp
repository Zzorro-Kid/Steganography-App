#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Stenographer.h"
#include <QFileDialog>
#include <QMessageBox>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupAllConnections();
}

void MainWindow::setupAllConnections()
{
    connect(ui->selectFileButton, &QPushButton::clicked, this, &MainWindow::onSelectFileButtonClicked);
    connect(ui->showInfoButton, &QPushButton::clicked, this, &MainWindow::onShowInfoButtonClicked);
    connect(ui->selectEmbedFileButton, &QPushButton::clicked, this, &MainWindow::onSelectEmbedFileButtonClicked);
    connect(ui->embedButton, &QPushButton::clicked, this, &MainWindow::onEmbedButtonClicked);
    connect(ui->selectExtractFileButton, &QPushButton::clicked, this, &MainWindow::onSelectExtractFileButtonClicked);
    connect(ui->extractButton, &QPushButton::clicked, this, &MainWindow::onExtractButtonClicked);
    connect(ui->selectCheckFileButton, &QPushButton::clicked, this, &MainWindow::onSelectCheckFileButtonClicked);
    connect(ui->checkButton, &QPushButton::clicked, this, &MainWindow::onCheckButtonClicked);
}

QString MainWindow::openFileDialog(const QString& dialogTitle)
{
    return QFileDialog::getOpenFileName(
        this,
        dialogTitle,
        "",
        "Images (*.bmp *.ppm)"
        );
}

void MainWindow::onSelectFileButtonClicked()
{
    QString selectedFilePath = openFileDialog("Выберите файл для просмотра информации");
    if (!selectedFilePath.isEmpty()) {
        ui->filePathLineEdit->setText(selectedFilePath);
    }
}

void MainWindow::onShowInfoButtonClicked()
{
    QString currentFilePath = ui->filePathLineEdit->text();

    if (currentFilePath.isEmpty()) {
        showErrorMessage("Ошибка", "Файл не выбран");
        return;
    }

    try {
        // Вариант 1: Если функция в глобальном пространстве
        std::string imageInfo = stego::get_image_info(currentFilePath.toStdString());

        ui->infoTextEdit->setText(QString::fromStdString(imageInfo));
    } catch (const std::exception& error) {
        showErrorMessage("Ошибка", error.what());
    }
}

void MainWindow::onSelectEmbedFileButtonClicked()
{
    QString selectedFilePath = openFileDialog("Выберите файл для встраивания сообщения");
    if (!selectedFilePath.isEmpty()) {
        ui->embedFilePathLineEdit->setText(selectedFilePath);
    }
}

void MainWindow::onEmbedButtonClicked()
{
    QString targetFilePath = ui->embedFilePathLineEdit->text();
    QString messageToEmbed = ui->messageTextEdit->toPlainText();

    if (targetFilePath.isEmpty() || messageToEmbed.isEmpty()) {
        showErrorMessage("Ошибка", "Необходимо указать файл и сообщение");
        return;
    }

    try {
        bool operationSuccessful = stego::embed_message_into_image(
            targetFilePath.toStdString(),
            messageToEmbed.toStdString()
            );

        ui->statusLabel->setText(operationSuccessful ? "Успешно!" : "Ошибка!");
    } catch (const std::exception& error) {
        showErrorMessage("Ошибка", error.what());
    }
}

void MainWindow::onSelectExtractFileButtonClicked()
{
    QString selectedFilePath = openFileDialog("Выберите файл для извлечения сообщения");
    if (!selectedFilePath.isEmpty()) {
        ui->extractFilePathLineEdit->setText(selectedFilePath);
    }
}

void MainWindow::onExtractButtonClicked()
{
    QString sourceFilePath = ui->extractFilePathLineEdit->text();

    if (sourceFilePath.isEmpty()) {
        showErrorMessage("Ошибка", "Файл не выбран");
        return;
    }

    try {
        std::string extractedMessage = stego::decode_message_from_image(sourceFilePath.toStdString());
        ui->extractedMessageTextEdit->setText(QString::fromStdString(extractedMessage));
    } catch (const std::exception& error) {
        showErrorMessage("Ошибка", error.what());
    }
}

void MainWindow::onSelectCheckFileButtonClicked()
{
    QString selectedFilePath = openFileDialog("Выберите файл для проверки вместимости");
    if (!selectedFilePath.isEmpty()) {
        ui->checkFilePathLineEdit->setText(selectedFilePath);
    }
}

void MainWindow::onCheckButtonClicked()
{
    QString targetFilePath = ui->checkFilePathLineEdit->text();
    QString testMessage = ui->checkMessageTextEdit->toPlainText();

    if (targetFilePath.isEmpty() || testMessage.isEmpty()) {
        showErrorMessage("Ошибка", "Необходимо указать файл и тестовое сообщение");
        return;
    }

    try {
        bool hasEnoughSpace = stego::check_capacity(
            targetFilePath.toStdString(),
            testMessage.toStdString()
            );

        ui->resultLabel->setText(hasEnoughSpace ? "Достаточно места" : "Недостаточно места");
    } catch (const std::exception& error) {
        showErrorMessage("Ошибка", error.what());
    }
}

void MainWindow::showErrorMessage(const QString& title, const QString& message)
{
    QMessageBox::warning(this, title, message);
}

MainWindow::~MainWindow()
{
    delete ui;
}
