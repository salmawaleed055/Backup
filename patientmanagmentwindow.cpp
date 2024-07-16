#include "patientmanagmentwindow.h"
#include "ui_patientmanagmentwindow.h"
#include <rescheduleappointmentwindow.h>
#include <bookappointmentwindow.h>
#include <chat.h>
#include <qpixmap.h>
#include<mainwindow.h>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <patient.h>
#include "patient.h"

void PatientManagmentWindow::loadPatientData() {
    // Assuming 'currpat' is the current patient
    currpat.loadAppointments();
    updateComboBoxes();
}


PatientManagmentWindow::PatientManagmentWindow(QWidget *parent,patient p) :
    QDialog(parent),
    ui(new Ui::PatientManagmentWindow),currentPat(p),
    submit(false) // Initialize submit as false
{
    QPixmap backgroundImage(":/Images/download.jpg");

    // Set the background image
    QBrush backgroundBrush(backgroundImage);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, backgroundBrush);
    this->setPalette(palette);

    ui->setupUi(this);
    //ui->labelUsername->setText(ui->labelUsername->text());
    QPixmap pix(":/Images/Imagepatientwindow");
    ui->comboBoxCancel->setVisible(false);
    ui->comboBoxReschedule->setVisible(false);
    //int w = ui->labelImage->width();
    ui->pushButtonSubmit->setVisible(false);
    ui->labelHello->setText("Hello "+currentPat.name);
    //int h = ui->labelImage->height();
    //ui->labelImage->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
    // ui->labelImage->setVisible(true);
    currpat.loadAppointments(); // Load appointments from file
    updateComboBoxes();
    for (auto it = currpat.appointments.begin(); it != currpat.appointments.end(); ++it) {
        QString appointment = it.key() + " (" + it.value() + ")";
        ui->comboBoxCancel->addItem(appointment);
        ui->comboBoxReschedule->addItem(appointment);
    }
}

PatientManagmentWindow::~PatientManagmentWindow()
{
    delete ui;
}
// void PatientManagmentWindow::setPatient(const patient &patient)
// {
//     currentPatient = patient;
// }
void PatientManagmentWindow::setUsername(const QString &username)
{
    QFont font1;
    font1.setFamily("Arial");
    font1.setPointSize(9);
    font1.setItalic(true);
    font1.setBold(true);

    QFont font2;
    font2.setFamily("Segoe UI");
    font2.setPointSize(16);
    ui->labelUsername->setFont(font1);
    ui->labelUsername->setText(username);
    ui->labelUsername->setFont(font2);
}
void PatientManagmentWindow::on_pushButtonBook_clicked()
{
    BookAppointmentWindow* book = new BookAppointmentWindow(this);
    book->exec();



}


void PatientManagmentWindow::on_pushButtonReschedule_clicked()
{
    ui->comboBoxReschedule->setVisible(true);
    ui->pushButtonSubmit->setVisible(true);
    ui->pushButtonCancel->setEnabled(false);
}


void PatientManagmentWindow::on_pushButtonCancel_clicked()
{
    ui->comboBoxCancel->setVisible(true);
    ui->pushButtonSubmit->setVisible(true);
    ui->pushButtonReschedule->setEnabled(false);

}

void PatientManagmentWindow::on_pushButtonChat_clicked()
{
    chat* chat =new class chat (this);
    chat->exec();
}

void PatientManagmentWindow::on_pushButtonMedical_Record_clicked()
{
    QString filePath = ":/Medical record file/medical record.txt";
    QString medicalRecord;

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString line;
            bool found = false;
            while (!in.atEnd()) {
                line = in.readLine().trimmed(); // Read and trim whitespace
                if (line.startsWith("Name: " + currentPat.name)) {
                    found = true;
                    medicalRecord += line + "\n";
                    while (!in.atEnd() && !line.isEmpty()) {
                        line = in.readLine().trimmed();
                        if (!line.isEmpty()) {
                            medicalRecord += line + "\n";
                        }
                    }
                    break;
                }
            }
            file.close();

            if (found) {
                QMessageBox::information(this, tr("Medical Record"), medicalRecord);
            } else {
                medicalRecord="Name: "+ currentPat.name+"\nAge "+ QString::number(currentPat.age)+"\nGender: "+currentPat.gender+"\nNo Medical Record\n";
                QMessageBox::information(this, tr("Error"), medicalRecord);
            }
        } else {
            QMessageBox::critical(this, tr("Error"), tr("Failed to open the file."));
        }
    }
}
void PatientManagmentWindow::addToAppointments(const QString &slot)
{
    // Determine selected specialty from UI, assuming it's stored in a member variable
    QString selectedSpecialty = "Selected Specialty"; // Replace with actual logic to get specialty

    // Update appointments map
    currpat.appointments[slot] = selectedSpecialty;

    // Update ComboBoxes in other windows (RescheduleAppointmentWindow and CancelAppointmentWindow)
    updateComboBoxes();
}


void PatientManagmentWindow::updateComboBoxes()
{
    // Clear existing items in combo boxes
    ui->comboBoxReschedule->clear();
    ui->comboBoxCancel->clear();

    QString fileName = "Appointments.txt";
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line;
        QStringList parts;
        bool found = false;

        while (!in.atEnd()) {
            line = in.readLine().trimmed();
            parts = line.split(":");

            if (parts.size() == 3) {
                QString username = parts[0].trimmed();
                QString slot = parts[1].trimmed();
                QString specialty = parts[2].trimmed();

                if (username == currpat.username) {
                    // Update current patient's appointments
                    currpat.appointments[slot] = specialty;

                    // Add to combo boxes
                    ui->comboBoxReschedule->addItem(slot + " - " + specialty);
                    ui->comboBoxCancel->addItem(slot + " - " + specialty);

                    found = true; // Flag to indicate appointments found for current patient
                } else if (found) {
                    // If appointments for current patient were found and now encountering other patient's data, stop processing
                    break;
                }
            }
        }

        if (!found) {
            qDebug() << "No appointments found for current patient:" << currpat.username;
        }

        file.close();
    } else {
        qDebug() << "Failed to open file for reading:" << file.errorString();
    }
}


void PatientManagmentWindow::on_pushButtonSubmit_clicked()
{
    if (ui->comboBoxCancel->isVisible()) {
        int currentIndex = ui->comboBoxCancel->currentIndex();
        if (currentIndex >= 0) {
            QString selectedItem = ui->comboBoxCancel->itemText(currentIndex);
            QString slotToRemove = selectedItem.section(" - ", 0, 0);

            // Remove appointment from current patient's data
            currpat.appointments.remove(slotToRemove);

            // Update combo box
            ui->comboBoxCancel->removeItem(currentIndex);

            // Save updated appointments to file
            currpat.saveAppointments();
        }
    }

    if (ui->comboBoxReschedule->isVisible()) {
        int currentIndex = ui->comboBoxReschedule->currentIndex();
        if (currentIndex >= 0) {
            QString selectedItem = ui->comboBoxReschedule->itemText(currentIndex);
            QString slotToRemove = selectedItem.section(" - ", 0, 0);

            // Remove appointment from current patient's data
            currpat.appointments.remove(slotToRemove);

            // Update combo box
            ui->comboBoxReschedule->removeItem(currentIndex);

            // Save updated appointments to file
            currpat.saveAppointments();

            // Open the book appointment window for rescheduling
            BookAppointmentWindow* app = new BookAppointmentWindow(this, currpat);
            app->exec();
        }
    }

}

void PatientManagmentWindow::setCurrentPatient(const patient& p)
{
    currpat = p;
    loadPatientData(); // Reload patient data with the new patient
}

void PatientManagmentWindow::on_pushButton_clicked()
{
    hide();
    MainWindow* win=new MainWindow(this);
    win->show();
}

