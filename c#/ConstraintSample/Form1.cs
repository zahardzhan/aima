using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using aima.search.csp;

namespace ConstraintSample
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Button btnHouses;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public Form1()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.btnHouses = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(24, 16);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.textBox1.Size = new System.Drawing.Size(408, 224);
			this.textBox1.TabIndex = 0;
			this.textBox1.Text = "textBox1";
			// 
			// btnHouses
			// 
			this.btnHouses.Location = new System.Drawing.Point(184, 256);
			this.btnHouses.Name = "btnHouses";
			this.btnHouses.TabIndex = 1;
			this.btnHouses.Text = "Houses";
			this.btnHouses.Click += new System.EventHandler(this.btnHouses_Click);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(456, 293);
			this.Controls.Add(this.btnHouses);
			this.Controls.Add(this.textBox1);
			this.Name = "Form1";
			this.Text = "Form1";
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}

		private void btnHouses_Click(object sender, System.EventArgs e)
		{
			CSP csp = HousesCSP.getMap();
			this.textBox1.Text = "Map Coloring - Backtracking " + System.Environment.NewLine;
			this.textBox1.Text += csp.backTrackingSearch() + System.Environment.NewLine;
               // System.out.println("Number of nodes: " + csp.getMetric());
			this.textBox1.Text += "Map Coloring - Minimum Conflicts ";
			this.textBox1.Text += (csp.mcSearch(100) == null ? "N/A" : csp.mcSearch(100).ToString());
		}
	}
}
