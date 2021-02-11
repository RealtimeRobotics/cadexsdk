using cadex;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace baseviewer
{
    public partial class BaseViewer : Form
    {
        public BaseViewer()
        {
            InitializeComponent();
        }

        public BaseViewerApplication ViewerApplication
        {
            get { return myApp; }
            set {
                myApp = value;
                myApp.ErrorMessage += OnErrorMessage;
                myApp.LoadingChanged += OnLoadingChanged;
            }
        }

        public ModelPrsWinForms_ViewPort Viewport
        {
            get { return myViewPort; }
        }

        public void OnLoadingChanged(bool theLoading)
        {
            myLoadingItem.Visible = theLoading;
        }

        private void OnErrorMessage(string theMessage)
        {
            MessageBox.Show(theMessage);
        }

        private void OnQuit (object sender, EventArgs es)
        {
            Application.Exit();
        }

        private void OnImport(object sender, EventArgs es)
        {
            var aFilename = ShowFileDialog();

            if (aFilename != string.Empty)
            {
                Parent.Text = "CAD Exchanger [" + aFilename + "]";
                myApp.Import(aFilename);
            }
        }

        private static string ShowFileDialog()
        {
            OpenFileDialog aFileDialog = new OpenFileDialog
            {
                InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Desktop),
                CheckFileExists  = true,
                CheckPathExists  = true,
                Filter           = "STEP Files (*.step)|*.stp",
                FilterIndex      = 2,
                RestoreDirectory = true,
                ShowReadOnly     = true
            };

            try
            {
                var result = aFileDialog.ShowDialog();
                if (result == DialogResult.OK & aFileDialog.OpenFile() != null)
                {
                    return aFileDialog.FileName;
                }
            }
            catch (Exception ex)
            {
                if (aFileDialog.FileName != string.Empty)
                {
                    MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
                }
            }

            return string.Empty;
        }

        protected BaseViewerApplication myApp;
        protected ModelPrsWinForms_ViewPort myViewPort;
    }
}
