using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using aima.search.framework;
using aima.search.uninformed;
using aima.search.informed;
using aima.search.nqueens;


namespace NQueensDemo
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Button btnBreadthFirst;
		private System.Windows.Forms.Button btnIterativeDeeping;
		private System.Windows.Forms.Button btnSimulatedAnnealing;
		private System.Windows.Forms.Button btnRecursiveDLS;
		private System.Windows.Forms.Button btnHillClimbing;
		private System.Windows.Forms.Button btnDepthFirst;
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
			this.btnBreadthFirst = new System.Windows.Forms.Button();
			this.btnIterativeDeeping = new System.Windows.Forms.Button();
			this.btnSimulatedAnnealing = new System.Windows.Forms.Button();
			this.btnRecursiveDLS = new System.Windows.Forms.Button();
			this.btnHillClimbing = new System.Windows.Forms.Button();
			this.btnDepthFirst = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(8, 8);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.textBox1.Size = new System.Drawing.Size(584, 272);
			this.textBox1.TabIndex = 0;
			this.textBox1.Text = "n Queens Demo";
			// 
			// btnBreadthFirst
			// 
			this.btnBreadthFirst.Location = new System.Drawing.Point(112, 288);
			this.btnBreadthFirst.Name = "btnBreadthFirst";
			this.btnBreadthFirst.Size = new System.Drawing.Size(80, 40);
			this.btnBreadthFirst.TabIndex = 1;
			this.btnBreadthFirst.Text = "Breadth First";
			this.btnBreadthFirst.Click += new System.EventHandler(this.btnBreadthFirst_Click);
			// 
			// btnIterativeDeeping
			// 
			this.btnIterativeDeeping.Location = new System.Drawing.Point(304, 288);
			this.btnIterativeDeeping.Name = "btnIterativeDeeping";
			this.btnIterativeDeeping.Size = new System.Drawing.Size(88, 40);
			this.btnIterativeDeeping.TabIndex = 2;
			this.btnIterativeDeeping.Text = "Iterative Deepening";
			this.btnIterativeDeeping.Click += new System.EventHandler(this.btnIterativeDeeping_Click);
			// 
			// btnSimulatedAnnealing
			// 
			this.btnSimulatedAnnealing.Location = new System.Drawing.Point(408, 288);
			this.btnSimulatedAnnealing.Name = "btnSimulatedAnnealing";
			this.btnSimulatedAnnealing.Size = new System.Drawing.Size(80, 40);
			this.btnSimulatedAnnealing.TabIndex = 3;
			this.btnSimulatedAnnealing.Text = "Simulated Annealing";
			this.btnSimulatedAnnealing.Click += new System.EventHandler(this.btnSimulatedAnnealing_Click);
			// 
			// btnRecursiveDLS
			// 
			this.btnRecursiveDLS.Location = new System.Drawing.Point(208, 288);
			this.btnRecursiveDLS.Name = "btnRecursiveDLS";
			this.btnRecursiveDLS.Size = new System.Drawing.Size(80, 40);
			this.btnRecursiveDLS.TabIndex = 4;
			this.btnRecursiveDLS.Text = "Recursive DLS";
			this.btnRecursiveDLS.Click += new System.EventHandler(this.btnRecursiveDLS_Click);
			// 
			// btnHillClimbing
			// 
			this.btnHillClimbing.Location = new System.Drawing.Point(504, 288);
			this.btnHillClimbing.Name = "btnHillClimbing";
			this.btnHillClimbing.Size = new System.Drawing.Size(80, 40);
			this.btnHillClimbing.TabIndex = 5;
			this.btnHillClimbing.Text = "Hill Climbing";
			this.btnHillClimbing.Click += new System.EventHandler(this.btnHillClimbing_Click);
			// 
			// btnDepthFirst
			// 
			this.btnDepthFirst.Location = new System.Drawing.Point(8, 288);
			this.btnDepthFirst.Name = "btnDepthFirst";
			this.btnDepthFirst.Size = new System.Drawing.Size(88, 40);
			this.btnDepthFirst.TabIndex = 6;
			this.btnDepthFirst.Text = "Depth First";
			this.btnDepthFirst.Click += new System.EventHandler(this.btnDepthFirst_Click);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 15);
			this.ClientSize = new System.Drawing.Size(600, 336);
			this.Controls.Add(this.btnDepthFirst);
			this.Controls.Add(this.btnHillClimbing);
			this.Controls.Add(this.btnRecursiveDLS);
			this.Controls.Add(this.btnSimulatedAnnealing);
			this.Controls.Add(this.btnIterativeDeeping);
			this.Controls.Add(this.btnBreadthFirst);
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
		private void printActions(ArrayList actions) 
		{
			this.textBox1.Text += System.Environment.NewLine;
			for (int i = 0; i < actions.Count; i++) 
			{
				string action = (string) actions[i];
				//System.out.println(action);
				this.textBox1.Text += action + System.Environment.NewLine;
			}
		}

		private void printInstrumentation(Hashtable properties) 
		{
			IEnumerator keys = properties.Keys.GetEnumerator();
			while (keys.MoveNext()) 
			{
				string key = keys.Current.ToString();
				string property = properties[key].ToString();
				this.textBox1.Text += (key + " : " + property);
			}
		}

		private void btnDepthFirst_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "NQueensDemo DFS -->" + System.Environment.NewLine;
			Problem problem =  new Problem(new NQueensBoard(8),new NQueensSuccessorFunction(), new NQueensGoalTest());
			Search search = new DepthFirstSearch(new GraphSearch());
			SearchAgent agent = new SearchAgent(problem, search);
			printActions(agent.getActions());
			printInstrumentation(agent.getInstrumentation());
		}

		private void btnBreadthFirst_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "NQueensDemo BFS -->" + System.Environment.NewLine;
			Problem problem =  new Problem(new NQueensBoard(8),new NQueensSuccessorFunction(), new NQueensGoalTest());
			Search search = new BreadthFirstSearch(new TreeSearch());
			SearchAgent agent2 = new SearchAgent(problem, search);
			printActions(agent2.getActions());
			printInstrumentation(agent2.getInstrumentation());
		}

		private void btnRecursiveDLS_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "NQueensDemo recursive DLS -->" + System.Environment.NewLine;

			Problem problem =  new Problem(new NQueensBoard(8),new NQueensSuccessorFunction(), new NQueensGoalTest());
			Search search = new DepthLimitedSearch(8);
			SearchAgent agent = new SearchAgent(problem, search);
			printActions(agent.getActions());
			printInstrumentation(agent.getInstrumentation());
		}

		private void btnIterativeDeeping_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "NQueensDemo Iterative DS -->" + System.Environment.NewLine;

			Problem problem =  new Problem(new NQueensBoard(8),new NQueensSuccessorFunction(), new NQueensGoalTest());
			Search search =  new IterativeDeepeningSearch();
			SearchAgent agent = new SearchAgent(problem,search);

			
			printActions(agent.getActions());
			printInstrumentation(agent.getInstrumentation());
		}

		private void btnSimulatedAnnealing_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "NQueensDemo Simulated Annealing -->" + System.Environment.NewLine;

			Problem problem =  new Problem(new NQueensBoard(8),new NQueensSuccessorFunction(), new NQueensGoalTest(),new QueensToBePlacedHeuristic());
			Search search =  new SimulatedAnnealingSearch();
			SearchAgent agent = new SearchAgent(problem,search);

			
			printActions(agent.getActions());
			printInstrumentation(agent.getInstrumentation());
		}

		private void btnHillClimbing_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "NQueensDemo HillClimbing -->" + System.Environment.NewLine;

			Problem problem =  new Problem(new NQueensBoard(8),new NQueensSuccessorFunction(), new NQueensGoalTest(),new QueensToBePlacedHeuristic());
			Search search =  new HillClimbingSearch();
			SearchAgent agent = new SearchAgent(problem,search);

			printActions(agent.getActions());
			printInstrumentation(agent.getInstrumentation());
		}
	}
}
