#include "nursewindow.h"
#include "ui_nursewindow.h"
#include "nurse.h"
#include <QMessageBox>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>
#include <QPixmap>
#include "MainWindow.h"

nursewindow::nursewindow(QWidget *parent,nurse n)
    : QDialog(parent)
    , ui(new Ui::nursewindow)
{
    ui->setupUi(this);
    nur =n;
    ui->label_Hellonur->setText("Hello Dr. "+ nur.username);
    QPixmap backgroundImage(":/Images/download.jpg");

    // Set the background image
    QBrush backgroundBrush(backgroundImage);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, backgroundBrush);
    this->setPalette(palette);

}

nursewindow::~nursewindow()
{
    delete ui;
}

void nursewindow::on_pushButton_profile_clicked()
{
    QMessageBox::information(this, tr("profile"), "Name: "+ nur.username + "\nGender: "+nur.gender +
                                                      "\nAge: "+ QString::number(nur.age) + "\nWorking day: "+ nur.days.join(", ") + "time from: "+ QString::number(nur.starttime)
                                                      + " to "+ QString::number(nur.endtime));
}


QString nursewindow::getAssignmentString(nurse& nuu)
{
    QString assignmentString;
    for (const auto& patient : nuu.patients)  //assignments instead of patients
    {
        assignmentString += patient + ", ";
    }
    if (!assignmentString.isEmpty())
    {
        assignmentString.chop(2); // Remove the trailing ", "
    }
    return assignmentString;
}
void nursewindow::on_pushButton_Schedule_clicked()
{
    QString scheduleText;
    for (const auto& day : nur.days)
    {
        scheduleText += day + " - " + QString::number(nur.starttime) + ":00 to " + QString::number(nur.endtime) + ":00\n";
    }
    // for (const auto& patient : nur.patients)
    // {
    //     scheduleText += patient + "\n";
    // }
    QMessageBox::information(this, tr("Schedule"), scheduleText);
}


void nursewindow::on_pushButton_Assignment_clicked()
{
    QString patientList;
    for (const auto& patient : nur.patients)
    {
        patientList += patient + "\n";
    }

    QMessageBox::information(this, tr("Patient List"), "Patients:\n" + patientList);
}


void nursewindow::on_pushButton_clicked()
{
    hide();
    MainWindow* win=new MainWindow(this);
    win->show();
}

