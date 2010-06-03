using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using aima.logic.propositional.algorithms;
using aima.logic.propositional.parsing;

namespace LogicDemos
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Button btnPLFCEntails;
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
			this.btnPLFCEntails = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(16, 16);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.textBox1.Size = new System.Drawing.Size(456, 240);
			this.textBox1.TabIndex = 0;
			this.textBox1.Text = "textBox1";
			// 
			// btnPLFCEntails
			// 
			this.btnPLFCEntails.Location = new System.Drawing.Point(24, 264);
			this.btnPLFCEntails.Name = "btnPLFCEntails";
			this.btnPLFCEntails.Size = new System.Drawing.Size(88, 40);
			this.btnPLFCEntails.TabIndex = 1;
			this.btnPLFCEntails.Text = "PLFCEntails Demo";
			this.btnPLFCEntails.Click += new System.EventHandler(this.btnPLFCEntails_Click);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 15);
			this.ClientSize = new System.Drawing.Size(496, 328);
			this.Controls.Add(this.btnPLFCEntails);
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

		private void btnPLFCEntails_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = (Environment.NewLine + "PLFCEntailsDemo" + Environment.NewLine );
			KnowledgeBase kb =  new KnowledgeBase();
			kb.tell(" (P => Q)");
			kb.tell("((L AND M) => P)");
			kb.tell("((B AND L) => M)");
			kb.tell("( (A AND P) => L)");
			kb.tell("((A AND B) => L)");
			kb.tell("(A)");
			kb.tell("(B)");
			//kb.tell("(P)");

			this.textBox1.Text += (Environment.NewLine + "Example from  page 220 of AIMA 2nd Edition");
			this.textBox1.Text +=(Environment.NewLine + "KnowledgeBsse consists of sentences");
			this.textBox1.Text +=(Environment.NewLine + " (P => Q)");
			this.textBox1.Text +=(Environment.NewLine + "((L AND M) => P)");
			this.textBox1.Text +=(Environment.NewLine + "((B AND L) => M)");
			this.textBox1.Text +=(Environment.NewLine + "( (A AND P) => L)");
			this.textBox1.Text +=(Environment.NewLine + "((A AND B) => L)");
			this.textBox1.Text +=(Environment.NewLine + "(A)");
			this.textBox1.Text +=(Environment.NewLine + "(B)");
			//this.textBox1.Text +=(Environment.NewLine + "(P)");

			displayPLFCEntailment(kb, "Q");
		}
		private PEParser parser = new PEParser();

		private PLFCEntails plfce = new PLFCEntails();
		private void displayPLFCEntailment(KnowledgeBase kb, String q) 
		{
			this.textBox1.Text +=("Running PLFCEntailment on knowledge base  " 
					   + " with query " + q + " gives " + plfce.plfcEntails(kb,q));
		}
	}
}
