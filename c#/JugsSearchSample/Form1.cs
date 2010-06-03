using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using aima.search.framework;
using aima.search.uninformed;
using aima.search.informed;

namespace JugsSearchSample
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Button btnJugs;
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
			this.btnJugs = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(24, 16);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.textBox1.Size = new System.Drawing.Size(552, 264);
			this.textBox1.TabIndex = 0;
			this.textBox1.Text = "Jugs!";
			// 
			// btnJugs
			// 
			this.btnJugs.Location = new System.Drawing.Point(40, 288);
			this.btnJugs.Name = "btnJugs";
			this.btnJugs.Size = new System.Drawing.Size(96, 40);
			this.btnJugs.TabIndex = 1;
			this.btnJugs.Text = "Do Jugs Demo";
			this.btnJugs.Click += new System.EventHandler(this.btnJugs_Click);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 15);
			this.ClientSize = new System.Drawing.Size(608, 344);
			this.Controls.Add(this.btnJugs);
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

		private void btnJugs_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = ("Jugs Puzzle -->" + System.Environment.NewLine);
        
			Q2State initialState = new Q2State();
			try 
			{
				Problem problem = new Problem(initialState, 
					new Q2SuccessorFunction(),
					new Q2GoalTest(),
					new Q2StepCostFunction());
            
				Search search = new BreadthFirstSearch(new TreeSearch());
				//Search search = new BreadthFirstSearch(new GraphSearch());
				//Search search = new DepthFirstSearch(new TreeSearch());
				//Search search = new DepthFirstSearch(new GraphSearch());
				//Search search = new DepthLimitedSearch(12);
				//Search search = new IterativeDeepeningSearch();
				//Search search = new AStarSearch(new TreeSearch());
            
				ArrayList solution = search.search(problem);
            
				if (solution.Count == 0) 
				{ //empty list means failure
					this.textBox1.Text += (System.Environment.NewLine + "No Solution" +System.Environment.NewLine);
				}
				//this.textBox1.Text += (solution + System.Environment.NewLine);
				for (int i = 0; i < solution.Count; i++)
				{
					this.textBox1.Text += solution[i].ToString() + System.Environment.NewLine;
				}
            
				//Printing metrics
				Metrics searchMetrics = search.getMetrics();
				IEnumerator iter = searchMetrics.keySet().GetEnumerator();
				while (iter.MoveNext()) 
				{
					string key = iter.Current.ToString();
					string value = searchMetrics.get(key);
					this.textBox1.Text += (key +": " + value);
				}
            
			} 
			catch (Exception ex) 
			{
				this.textBox1.Text += ex.Message;
			}
		}
	}
}
