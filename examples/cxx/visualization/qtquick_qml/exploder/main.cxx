// ****************************************************************************
// $Id$
//
// Copyright (C) 2008-2014, Roman Lygin. All rights reserved.
// Copyright (C) 2014-2020, CADEX. All rights reserved.
//
// This file is part of the CAD Exchanger software.
//
// You may use this file under the terms of the BSD license as follows:
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// ****************************************************************************


#include "ExploderApplication.hxx"
#include <cadex/LicenseManager_Activate.h>
#include <QtCore/QUrl>
#include <QtWidgets/QApplication>

#include "../../../cadex_license.cxx"

using namespace cadex;

int main (int argc, char *argv[])
{
    auto aKey = LicenseKey::Value();

    //activate the license (aKey must be defined in cadex_license.cxx)
    if (!CADExLicense_Activate (aKey)) {
        qCritical ("Failed to activate CAD Exchanger license.");
        return 1;
    }

    // Must set dpi scaling before creating an application.
    QCoreApplication::setAttribute (Qt::AA_EnableHighDpiScaling);

    // Create QApplication because Qt.labs.platform module requires Qt Widgets library.
    // For more information see https://doc.qt.io/qt-5.10/qml-qt-labs-platform-filedialog.html
    QApplication app (argc, argv);

    ExploderApplication anApp;
    if (anApp.Initialize (QUrl ("qrc:/qml/ExploderWindow.qml"), "viewPort")) {
        return app.exec();
    }

    return 0;
}
