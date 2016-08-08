/*
 * Copyright 2016 Jan von Cosel
 *
 * This file is part of orbitalviewer.
 *
 * orbitalviewer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * orbitalviewer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have recieved a copy of the GNU General Public License
 * along with orbitalviewer. If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef Q_MOC_RUN
    #include <chemkit/moleculefile.h>
    #include <chemkit/graphicscamera.h>
#endif

#include "orbviewwindow.h"
#include "ui_orbviewwindow.h"

OrbViewWindow::OrbViewWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrbViewWindow)
{
    m_file = 0;

    ui->setupUi(this);

    connect(ui->actionOpen, SIGNAL(triggered()), SLOT(openFile()));
}

OrbViewWindow::~OrbViewWindow()
{
    delete ui;
}

void OrbViewWindow::openFile()
{
    std::vector<std::string> formats = chemkit::MoleculeFile::formats();
    std::sort(formats.begin(), formats.end());

    QString formatsString;
    foreach(const std::string &format, formats)
        formatsString += QString("*.%1 ").arg(format.c_str());

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), 0, QString("Molecule Files (%1);;All Files (*.*)").arg(formatsString));

    if(!fileName.isEmpty())
        openFile(fileName);
}

void OrbViewWindow::openFile(const QString &fileName)
{
    // close current file
    closeFile();

    // open and read file
    QByteArray fileNameString = fileName.toLatin1();
    chemkit::MoleculeFile *file = new chemkit::MoleculeFile(fileNameString.constData());

    if(!file->read())
    {
        QMessageBox::critical(this, "Error", QString("Error opening file: %1").arg(file->errorString().c_str()));
        delete file;
        return;
    }

    // set new file
    m_file = file;
    emit fileChanged(m_file);

    // set new molecule
    if(file->moleculeCount() > 0)
        setMolecule(file->molecule());
}

void OrbViewWindow::closeFile()
{
    // remove molecule
    setMolecule(boost::shared_ptr<chemkit::Molecule>());

    // remove file
    delete m_file;
    m_file = 0;
    emit fileChanged(m_file);
}

void OrbViewWindow::quit()
{
    closeFile();
    qApp->quit();
}

void OrbViewWindow::setMolecule(const boost::shared_ptr<chemkit::Molecule> &molecule)
{
    if(m_molecule == molecule)
        return;

    // remove old molecule item
    if(m_moleculeItem){
        ui->molView->deleteItem(m_moleculeItem);
        m_moleculeItem = 0;
    }

    // set molecule
    m_molecule = molecule;

    // add new molecule item
    if(molecule)
    {
        m_moleculeItem = new chemkit::GraphicsMoleculeItem(molecule.get());
        ui->molView->addItem(m_moleculeItem);
    }

    centerCamera();

    // notify observers
    emit moleculeChanged(molecule.get());
}

void OrbViewWindow::centerCamera()
{
    if(m_molecule)
    {
        ui->molView->camera()->lookAt(m_molecule->center().cast<float>());
        ui->molView->update();
    }
}
