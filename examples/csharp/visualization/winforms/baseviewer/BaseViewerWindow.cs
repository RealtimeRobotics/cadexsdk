using cadex;
using System;
using System.Windows.Forms;

namespace baseviewer
{
    public partial class BaseViewerWindow : Form
    {
        public BaseViewerWindow()
        {
            InitializeComponent();

            myViewer.ViewerApplication = new BaseViewerApplication(myViewer);
            myViewer.Show();
        }
    }
}
