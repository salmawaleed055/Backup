#include "bookappointmentwindow.h"
#include "ui_bookappointmentwindow.h"
#include <qlist.h>
#include <QListWidgetItem>
#include <patient.h>
#include <patientmanagmentwindow.h>//>
#include "users.h"
#include "patient.h"
#include "drclass.h"
#include "doctor.h"


BookAppointmentWindow::BookAppointmentWindow(QWidget *parent,patient p)
    : QDialog(parent)
    , ui(new Ui::BookAppointmentWindow)
{
    ui->setupUi(this);
    patient currentpat;
    QPixmap backgroundImage(":/Images/download.jpg");

    // Set the background image
    QBrush backgroundBrush(backgroundImage);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, backgroundBrush);
    this->setPalette(palette);

    connect(ui->radioButton_Nutrition, &QRadioButton::clicked, this, &BookAppointmentWindow::on_radioButton_Nutrition_clicked);
    connect(ui->radioButton_OG, &QRadioButton::clicked, this, &BookAppointmentWindow::on_radioButton_OG_clicked);
    connect(ui->radioButton_Ophthalmology, &QRadioButton::clicked, this, &BookAppointmentWindow::on_radioButton_Ophthalmology_clicked);
    connect(ui->radioButton_internalmedicine, &QRadioButton::clicked, this, &BookAppointmentWindow::on_radioButton_internalmedicine_clicked);
    connect(ui->radioButton_Dermatology, &QRadioButton::clicked, this, &BookAppointmentWindow::on_radioButton_Dermatology_clicked);
    connect(ui->slotsListView, &QListWidget::itemClicked, this, &BookAppointmentWindow::on_slotsListView_itemClicked);
    // connect(ui->pushButtonSubmit, &QPushButton::clicked, this, &BookAppointmentWindow::on_pushButtonSubmit_clicked);
}

BookAppointmentWindow::~BookAppointmentWindow()
{
    delete ui;
}
void BookAppointmentWindow::clearSlotsList()
{
    ui->slotsListView->clear();
}
void BookAppointmentWindow::addSlotToList(const QString &slot)
{
    QListWidgetItem *item = new QListWidgetItem(slot);
    ui->slotsListView->addItem(item);
}



void BookAppointmentWindow::on_radioButton_Nutrition_clicked()
{
    ui->label_Available_slots->setText("Available slots and doctors are:");
    clearSlotsList();
    for (int i=0;i<Nutrition.size();i++)
    {
        for (int j=0;j<Nutrition[i].days.size();j++)
        {
            addSlotToList(Nutrition[i].username+" on "+Nutrition[i].days[j]+" from "+QString::number(Nutrition[i].starttime)+" to "+QString::number(Nutrition[i].endtime));
        }
    }

    // addSlotToList("Slot A");
    // addSlotToList("Slot B");
    // addSlotToList("Slot C");
}


void BookAppointmentWindow::on_radioButton_OG_clicked()
{
    ui->label_Available_slots->setText("Available slots and doctors are:");
    clearSlotsList();
    for (int i=0;i<OG.size();i++)
    {
        for (int j=0;j<OG[i].days.size();j++)
        {
            addSlotToList(OG[i].username+" on "+OG[i].days[j]+" from "+QString::number(OG[i].starttime)+" to "+QString::number(OG[i].endtime));
        }
    }

}


void BookAppointmentWindow::on_radioButton_Ophthalmology_clicked()
{
    ui->label_Available_slots->setText("Available slots and doctors are:");
    clearSlotsList();
    for (int i=0;i<oph.size();i++)
    {
        for (int j=0;j<oph[i].days.size();j++)
        {
            addSlotToList(oph[i].username+" on "+oph[i].days[j]+" from "+QString::number(oph[i].starttime)+" to "+QString::number(oph[i].endtime));
        }
    }

}


void BookAppointmentWindow::on_radioButton_internalmedicine_clicked()
{
    ui->label_Available_slots->setText("Available slots and doctors are:");
    clearSlotsList();
    for (int i=0;i<IM.size();i++)
    {
        for (int j=0;j<IM[i].days.size();j++)
        {
            addSlotToList(IM[i].username+" on "+IM[i].days[j]+" from "+QString::number(IM[i].starttime)+" to "+QString::number(IM[i].endtime));
        }
    }

}


void BookAppointmentWindow::on_radioButton_Dermatology_clicked()
{
    ui->label_Available_slots->setText("Available slots and doctors are:");
    clearSlotsList();
    for (int i=0;i<Derm.size();i++)
    {
        for (int j=0;j<Derm[i].days.size();j++)
        {
            addSlotToList(Derm[i].username+" on "+Derm[i].days[j]+" from "+QString::number(Derm[i].starttime)+" to "+QString::number(Derm[i].endtime));
        }
    }
}


void BookAppointmentWindow::on_slotsListView_itemClicked(QListWidgetItem *item)
{
    QString selectedSlot = item->text();
    QString selectedSpecialty;

    if (ui->radioButton_Nutrition->isChecked()) {
        selectedSpecialty = "Nutrition";
    } else if (ui->radioButton_OG->isChecked()) {
        selectedSpecialty = "OG";
    } else if (ui->radioButton_Ophthalmology->isChecked()) {
        selectedSpecialty = "Ophthalmology";
    } else if (ui->radioButton_internalmedicine->isChecked()) {
        selectedSpecialty = "Internal Medicine";
    } else if (ui->radioButton_Dermatology->isChecked()) {
        selectedSpecialty = "Dermatology";
    }

    if (!selectedSpecialty.isEmpty()) {
        // Update parent window's patient data
        PatientManagmentWindow *parentWindow = qobject_cast<PatientManagmentWindow *>(parent());
        if (parentWindow) {
            parentWindow->currpat.appointments[selectedSlot] = selectedSpecialty;
            parentWindow->currpat.saveAppointments(); // Save appointments to file for parent window's patient
            parentWindow->updateComboBoxes(); // Update combo boxes in parent window
        }
        currpat.appointments[selectedSlot] = selectedSpecialty;
        currpat.saveAppointments(); // Save appointments to file for current patient
    }

}

void BookAppointmentWindow::on_pushButtonSubmit_clicked()     ///not handeled yet
{
    //submitClicked = true;
    //int i= ui->slotsListView->currentIndex();
    QString selectedSlot;
    QListWidgetItem *currentItem = ui->slotsListView->currentItem();
    if(currentItem){
     selectedSlot = currentItem->text();
    QString selectedSpecialty;

    if (ui->radioButton_Nutrition->isChecked()) {
        selectedSpecialty = "Nutrition";
    } else if (ui->radioButton_OG->isChecked()) {
        selectedSpecialty = "OG";
    } else if (ui->radioButton_Ophthalmology->isChecked()) {
        selectedSpecialty = "Ophthalmology";
    } else if (ui->radioButton_internalmedicine->isChecked()) {
        selectedSpecialty = "Internal Medicine";
    } else if (ui->radioButton_Dermatology->isChecked()) {
        selectedSpecialty = "Dermatology";
    }

    //we still need to push_back(currpat.name) to the selected dr vector for the patientschedule only (the only remaining part in the patient part)
    if (selectedSpecialty == "Nutrition") {
        for (int i = 0; i < Nutrition.size(); i++) {
            if (selectedSlot.contains(Nutrition[i].username)) {
                Nutrition[i].patients.push_back(currpat.name);
                break;
            }
        }
    } else if (selectedSpecialty == "OG") {
        for (int i = 0; i < OG.size(); i++) {
            if (selectedSlot.contains(OG[i].username)) {
                OG[i].patients.push_back(currpat.name);

                break;
            }
        }
    } else if (selectedSpecialty == "Ophthalmology") {
        for (int i = 0; i < oph.size(); i++) {
            if (selectedSlot.contains(oph[i].username)) {
                oph[i].patients.push_back(currpat.name);
                break;
            }
        }
    } else if (selectedSpecialty == "Internal Medicine") {
        for (int i = 0; i < IM.size(); i++) {
            if (selectedSlot.contains(IM[i].username)) {
                IM[i].patients.push_back(currpat.name);

                break;
            }
        }
    } else if (selectedSpecialty == "Dermatology") {
        for (int i = 0; i < Derm.size(); i++) {
            if (selectedSlot.contains(Derm[i].username)) {
                Derm[i].patients.push_back(currpat.name);
                break;
            }
        }
    }
    else{
         qDebug() << "No item selected in slotsListView.";
        ui->labelERROR->setText("Please select a slot.");

    }
    }


    //  PatientManagmentWindow *parentWindow = qobject_cast<PatientManagmentWindow *>(parent());
    //if (parentWindow) {
    //    parentWindow->currpat.appointments[selectedSlot] = selectedSpecialty;
    //    parentWindow->updateComboBoxes(); // Update the combo boxes
    // }
    // Display the schedule in the doctor's window
    //doctor doctorWindow(this, *findDoctorByUsername(selectedSlot));
    //doctorWindow.exec();
    hide();
}
// drclass* BookAppointmentWindow::findDoctorByUsername(const QString& username)
// {
//     for (auto& doc : Nutrition) {
//         if (doc.username == username) {
//             return &doc;
//         }
//     }
//     for (auto& doc : OG) {
//         if (doc.username == username) {
//             return &doc;
//         }
//     }
//     for (auto& doc : oph) {
//         if (doc.username == username) {
//             return &doc;
//         }
//     }
//     for (auto& doc : IM) {
//         if (doc.username == username) {
//             return &doc;
//         }
//     }
//     for (auto& doc : Derm) {
//         if (doc.username == username) {
//             return &doc;
//         }
//     }
//     return nullptr;
// }

