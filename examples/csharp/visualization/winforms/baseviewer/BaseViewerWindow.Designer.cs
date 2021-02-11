using System.Windows.Forms;
using System.Drawing;
using cadex;

namespace baseviewer
{
    partial class BaseViewerWindow
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.SuspendLayout();
            this.Text = "CAD Exchanger";
            this.IsMdiContainer = false;
            this.ClientSize = new System.Drawing.Size(1000, 600);

            // 
            // myViewer
            // 
            myViewer = new BaseViewer();
            myViewer.ClientSize = this.ClientSize;
            myViewer.Dock = DockStyle.Fill;

            // 
            // BaseViewerWindow
            // 
            this.Controls.Add(myViewer);

            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion

        private BaseViewer myViewer;
    }
}

