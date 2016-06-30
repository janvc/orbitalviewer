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


#include "orbviewwindow.h"
#include "ui_orbviewwindow.h"

OrbViewWindow::OrbViewWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrbViewWindow)
{
    ui->setupUi(this);
}

OrbViewWindow::~OrbViewWindow()
{
    delete ui;
}
