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


#ifndef ORBVIEWWINDOW_H
#define ORBVIEWWINDOW_H

#include <QMainWindow>

#ifndef Q_MOC_RUN
    #include <chemkit/molecule.h>
    #include <chemkit/moleculefileformat.h>
    #include <chemkit/graphicsmoleculeitem.h>
#endif


namespace Ui
{
    class OrbViewWindow;
}

class OrbViewWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OrbViewWindow(QWidget *parent = 0);
    ~OrbViewWindow();

    void setMolecule(const boost::shared_ptr<chemkit::Molecule> &molecule);

public slots:
    void openFile();
    void openFile(const QString &fileName);
    void closeFile();
    void quit();
    void centerCamera();

signals:
    void fileChanged(chemkit::MoleculeFile *file);
    void moleculeChanged(chemkit::Molecule *molecule);

private:
    Ui::OrbViewWindow *ui;

    chemkit::MoleculeFile *m_file;
    boost::shared_ptr<chemkit::Molecule> m_molecule;
    chemkit::GraphicsMoleculeItem *m_moleculeItem;
};

#endif // ORBVIEWWINDOW_H
