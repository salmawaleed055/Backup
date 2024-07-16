#include "doctor.h"
#include "ui_doctor.h"
#include "drclass.h"
#include "drclass.cpp"
#include <QFile>
#include <QMessageBox>
#include <QString>
#include "MainWindow.h"

doctor::doctor(QWidget *parent, drclass doc)
    : QDialog(parent)

    , ui(new Ui::doctor)

{
    ui->setupUi(this);
    currdoc=doc;
    ui->label_HelloDr->setText("Hello Dr. "+ doc.username);
    QPixmap backgroundImage(":/Images/download.jpg");

    // Set the background image
    QBrush backgroundBrush(backgroundImage);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, backgroundBrush);
    this->setPalette(palette);
}

doctor::~doctor()
{
    delete ui;
}

void doctor::on_pushButton_profile_clicked()
{
   // QString profile = "Name: "+currdoc.username;
    ///continue
    QMessageBox::information(this, tr("profile"), "Name: "+ currdoc.username +"\nSpecialization" + currdoc.specialization + "\nGender: "+currdoc.gender +
                                                     "\nAge: "+ QString::number(currdoc.age) + "\nWorking day: "+ currdoc.days.join(", ") + "time from: "+ QString::number(currdoc.starttime)
                                                      + " to "+ QString::number(currdoc.endtime));
}



QString doctor::getAssignmentString(drclass& doc)
{
    QString assignmentString;
    for (const auto& patient : doc.patients)  //assignments instead of patients
    {
        assignmentString += patient + ", ";
    }
    if (!assignmentString.isEmpty())
    {
        assignmentString.chop(2); // Remove the trailing ", "
    }
    return assignmentString;
}



void doctor::on_pushButton_profile_2_clicked()
{
    QString patientList="";
    for (const auto& patient : currdoc.patients)
    {
        patientList += patient + "\n";
    }


    QMessageBox::information(this, tr("Patient List"), "Patients:\n" + patientList);
}


void doctor::on_pushButton_schedule_clicked()
{
    QString scheduleText;
    for (const auto& day : currdoc.days)
    {
        scheduleText += day + " - " + QString::number(currdoc.starttime) + ":00 to " + QString::number(currdoc.endtime) + ":00\n";
    }
    for (const auto& patient : currdoc.patients)
    {
        scheduleText += patient + "\n";
    }
    QMessageBox::information(this, tr("Schedule"), scheduleText);
}


void doctor::on_pushButton_clicked()
{
    hide();
    MainWindow* win=new MainWindow(this);
    win->show();
}

