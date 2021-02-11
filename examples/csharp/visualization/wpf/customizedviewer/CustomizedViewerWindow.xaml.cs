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


using baseviewer;
using cadex;
using System;
using System.Windows;
using System.Windows.Media;

namespace customizedviewer
{
    /// <summary>
    /// Interaction logic for CustomizedViewerWindow.xaml
    /// </summary>
    public partial class CustomizedViewerWindow : Window
    {
        public CustomizedViewerWindow()
        {
            InitializeComponent();
            myViewer.ViewerApplication = new BaseViewerApplication(myViewer);
            myViewer.SizeChanged += ChangeViewCubeGeometry;

            ChangeBackgroundStyle();
            ChangeViewCubeStyle();
            ChangeMenuStyle();
        }

        void ChangeBackgroundStyle()
        {
            myViewer.Viewport.BackgroundStyle = new ModelPrs_BackgroundStyle(new ModelData_Color(0x00303030));
        }

        void ChangeViewCubeStyle()
        {
            var aTextColor = new ModelData_Color(Convert.ToInt32(0x00949494));
            var aViewCubeStyle = new ModelPrs_ViewCubeStyle();
            aViewCubeStyle.SetTextColor(aTextColor);
            aViewCubeStyle.SetTrihedronTextColor(aTextColor);
            aViewCubeStyle.SetNormalColor(new ModelData_Color(Convert.ToInt32(0x006e6e6e)));
            aViewCubeStyle.SetHoveredColor(new ModelData_Color(Convert.ToInt32(0x00545454)));
            aViewCubeStyle.SetPressedColor(new ModelData_Color(Convert.ToInt32(0x00474747)));
            myViewer.Viewport.ViewCubeStyle = aViewCubeStyle;
        }

        void ChangeMenuStyle()
        {
            var aMenuColor = new ModelData_Color(Convert.ToInt32(0x006e6e6e));
            myViewer.myMenu.Background = new SolidColorBrush(Color.FromScRgb(1.0f, aMenuColor.R(), aMenuColor.G(), aMenuColor.B()));
            myViewer.myFileMenuItem.Background = new SolidColorBrush(Color.FromScRgb(1.0f, aMenuColor.R(), aMenuColor.G(), aMenuColor.B()));
        }

        void ChangeViewCubeGeometry(object sender, SizeChangedEventArgs e)
        {
            var aViewCubeMargins = 10;
            var aWidth = e.NewSize.Width;
            var aHeight = e.NewSize.Height;

            var aViewCubeSize = Math.Max(Math.Min(aWidth, aHeight) / 5, 200);
            var aMinLeft = new ModelData_Point2dd(aWidth - aViewCubeMargins - aViewCubeSize,
                                                   aViewCubeMargins);
            var aMaxRight = new ModelData_Point2dd(aMinLeft.X() + aViewCubeSize,
                                                    aViewCubeMargins + aViewCubeSize);
            myViewer.Viewport.ViewCubeGeometry = new ModelData_Box2d(aMinLeft, aMaxRight);
        }
    }
}
