using cadex;
using Microsoft.Win32;
using System;
using System.Windows;
using System.Windows.Controls;

namespace baseviewer
{
    /// <summary>
    /// Interaction logic for BaseViewer.xaml
    /// </summary>
    public partial class BaseViewer : UserControl
    {
        public BaseViewer()
        {
            InitializeComponent();
        }

        public ModelPrsWPF_ViewPort Viewport
        {
            get { return myViewport; }
        }

        public bool loading
        {
            get { return myLoadingItem.Visibility == Visibility.Visible; }
            set { myLoadingItem.Visibility = value ? Visibility.Visible : Visibility.Hidden; }
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

        private void onImport(object sender, System.EventArgs e)
        {
            var aFilename = ShowFileDialog();

            if (aFilename != string.Empty)
            {
                foreach (Window aWindow in Application.Current.Windows)
                {
                    if (aWindow.IsActive)
                    {
                        aWindow.Title = "CAD Exchanger [" + aFilename + "]";
                        break;
                    }
                }

                myApp.Import(aFilename);
            }
        }

        private static string ShowFileDialog()
        {
            OpenFileDialog anOpenFileDialog = new OpenFileDialog
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
                var result = anOpenFileDialog.ShowDialog();
                if (result == true & anOpenFileDialog.OpenFile() != null)
                {
                    return anOpenFileDialog.FileName;
                }
            }
            catch (Exception ex)
            {
                if (anOpenFileDialog.FileName != String.Empty)
                {
                    MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
                }
            }

            return string.Empty;
        }

        private void onQuit(object sender, RoutedEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }

        private void OnErrorMessage(string theMessage)
        {
            MessageBox.Show(theMessage);
        }

        private void OnLoadingChanged(bool theLoading)
        {
            loading = theLoading;
        }

        protected BaseViewerApplication myApp;
    }
}
