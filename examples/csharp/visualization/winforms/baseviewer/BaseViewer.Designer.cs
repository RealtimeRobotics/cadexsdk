using System.Windows.Forms;
using System.Drawing;
using cadex;

namespace baseviewer
{
    partial class BaseViewer
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
            this.TopLevel = false;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Size = new System.Drawing.Size(1000, 600);

            // 
            // myMenu
            // 
            myMenu = new MenuStrip();
            myMenu.Dock = DockStyle.Fill;

            var aFileMenu = new ToolStripMenuItem("&File");
            myMenu.Items.Add(aFileMenu);

            var anImportMenuItem = new ToolStripMenuItem("&Import");
            anImportMenuItem.Click += OnImport;
            aFileMenu.DropDownItems.Add(anImportMenuItem);

            var anExitMenuItem = new ToolStripMenuItem("&Quit");
            anExitMenuItem.Click += OnQuit;
            aFileMenu.DropDownItems.Add(anExitMenuItem);

            // 
            // myViewPort
            //
            myViewPort = new ModelPrsWinForms_ViewPort();
            myViewPort.Dock = DockStyle.Fill;

            // 
            // aLayout
            //
            TableLayoutPanel aLayout = new TableLayoutPanel();
            aLayout.RowStyles.Clear();
            aLayout.ColumnStyles.Clear();
            aLayout.RowCount += 2;
            aLayout.ColumnCount += 1;
            aLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100.0F));
            aLayout.RowStyles.Add(new RowStyle(SizeType.Absolute, myMenu.Height));
            aLayout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
            aLayout.Controls.Add(myMenu, 0, 0);
            aLayout.Controls.Add(myViewPort, 0, 1);
            aLayout.Dock = DockStyle.Fill;

            // 
            // myLoadingItem
            // 
            myLoadingItem = new System.Windows.Forms.Label();
            myLoadingItem.Text = "Loading...";
            myLoadingItem.TextAlign = ContentAlignment.MiddleCenter;
            myLoadingItem.Font = new Font(Font.Name, 13, FontStyle.Regular);
            myLoadingItem.Size = new Size(myLoadingItem.PreferredWidth, myLoadingItem.PreferredHeight);
            myLoadingItem.MaximumSize = myLoadingItem.Size;
            myLoadingItem.BackColor = Color.White;
            myLoadingItem.Visible = false;
            myLoadingItem.Dock = DockStyle.Bottom;

            // 
            // BaseViewer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(myLoadingItem);
            this.Controls.Add(aLayout);
            this.MainMenuStrip = this.myMenu;
            this.Name = "BaseViewer";
            this.Text = "CAD Exchanger";
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion

        private System.Windows.Forms.MenuStrip myMenu;
        private System.Windows.Forms.Label     myLoadingItem;
    }
}

