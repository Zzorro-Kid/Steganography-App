#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSelectFileButtonClicked();
    void onShowInfoButtonClicked();
    void onSelectEmbedFileButtonClicked();
    void onEmbedButtonClicked();
    void onSelectExtractFileButtonClicked();
    void onExtractButtonClicked();
    void onSelectCheckFileButtonClicked();
    void onCheckButtonClicked();

private:
    Ui::MainWindow *ui;

    void setupAllConnections();
    QString openFileDialog(const QString& dialogTitle);
    void showErrorMessage(const QString& title, const QString& message);
};

#endif // MAINWINDOW_H
