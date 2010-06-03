using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using aima.search.framework;
using aima.search.uninformed;
using aima.search.informed;


namespace SearchSamples
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Button btnJocks;
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
			this.btnJocks = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(8, 8);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.textBox1.Size = new System.Drawing.Size(472, 224);
			this.textBox1.TabIndex = 0;
			this.textBox1.Text = "";
			// 
			// btnJocks
			// 
			this.btnJocks.Location = new System.Drawing.Point(16, 256);
			this.btnJocks.Name = "btnJocks";
			this.btnJocks.TabIndex = 1;
			this.btnJocks.Text = "Jocks/Nerds";
			this.btnJocks.Click += new System.EventHandler(this.btnJocks_Click);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(488, 301);
			this.Controls.Add(this.btnJocks);
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

		private void btnJocks_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "";
			JocksNerdsState initialState = new JocksNerdsState();
			try 
			{
				Problem problem = new Problem(initialState, 
					new JocksNerdsSuccessorFunction(),
					new JocksNerdsGoalTest());
            
				//Search search = new BreadthFirstSearch(new TreeSearch());
				//Search search = new BreadthFirstSearch(new GraphSearch());

				//this one never ends because it tries to traverse a tree of effectively infinite depth
				//Search search = new DepthFirstSearch(new TreeSearch());
				//Search search = new DepthFirstSearch(new GraphSearch());

				//Search search = new DepthLimitedSearch(12);
				//Search search = new IterativeDeepeningSearch();

				//Search search = new AStarSearch(new GraphSearch());
				//Search search = new GreedyBestFirstSearch(new GraphSearch());
				//Search search = new HillClimbingSearch();
				Search search = new SimulatedAnnealingSearch();

            
				ArrayList solution = search.search(problem);
            
				if (solution.Count == 0) 
				{ //empty list means failure
					//System.out.println("\nNo Solution\n");
					this.textBox1.Text = System.Environment.NewLine + "No Solution";
				}
				for (int i = 0; i < solution.Count; i++)
				{
					this.textBox1.Text += solution[i].ToString() + System.Environment.NewLine;
				}
            
				//Printing metrics
				Metrics searchMetrics = search.getMetrics();
				//ArrayList iter = (ArrayList)searchMetrics.keySet();
				ICollection col = searchMetrics.keySet();
				IEnumerator iter = col.GetEnumerator();
				//iter.GetEnumerator();
				//Array r = new Array();
				//iter.MoveNext();
				
				//iter.
            
            
				while(iter.MoveNext())
				{
					string key =  iter.Current.ToString();
					string val = searchMetrics.get(key);
					this.textBox1.Text += System.Environment.NewLine + key + ": " + val;
					//iter.MoveNext();
				}
            
			} 
			catch (Exception ex) 
			{
				//e.printStackTrace();
				this.textBox1.Text += ex.Message;
			}
		}
		
	}
}
