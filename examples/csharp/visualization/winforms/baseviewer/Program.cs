using cadex;
using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace baseviewer
{
    static class Program
    {
        // For more information see https://stackoverflow.com/questions/8836093/how-can-i-specify-a-dllimport-path-at-runtime
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool SetDllDirectory(string lpPathName);

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // Add runtime path to CAD Exchanger libraries (e.g. use libraries compiled with Visual Studio 2015)
            SetDllDirectory("../../../../../../../win64/vc14.1/bin");

            string aKey = LicenseKey.Value();

            // Activate the license (aKey must be defined in cadex_license.cs)
            if (!LicenseManager.Activate(aKey))
            {
                MessageBox.Show("Failed to activate CAD Exchanger license.");
                Application.Exit();
            }

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new BaseViewerWindow());
        }
    }
}
