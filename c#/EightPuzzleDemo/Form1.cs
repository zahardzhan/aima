using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using aima.search.framework;
using aima.search.uninformed;
using aima.search.informed;
using aima.search.eightpuzzle;

namespace EightPuzzleDemo
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Button btnRecursiveDLS;
		private System.Windows.Forms.Button btnAStarMan;
		private System.Windows.Forms.Button btnGreedyBestFirst;
		private System.Windows.Forms.Button btnAStar;
		private System.Windows.Forms.Button btnGreedyBestFirstMan;
		private System.Windows.Forms.Button btnRecursiveIDLS;
		private System.Windows.Forms.Button btnSimulatedAnnealing;
		private System.Windows.Forms.Button btnIDLS;
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
			this.btnRecursiveDLS = new System.Windows.Forms.Button();
			this.btnAStarMan = new System.Windows.Forms.Button();
			this.btnGreedyBestFirst = new System.Windows.Forms.Button();
			this.btnAStar = new System.Windows.Forms.Button();
			this.btnGreedyBestFirstMan = new System.Windows.Forms.Button();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.btnSimulatedAnnealing = new System.Windows.Forms.Button();
			this.btnIDLS = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// btnRecursiveDLS
			// 
			this.btnRecursiveDLS.Location = new System.Drawing.Point(8, 280);
			this.btnRecursiveDLS.Name = "btnRecursiveDLS";
			this.btnRecursiveDLS.Size = new System.Drawing.Size(88, 48);
			this.btnRecursiveDLS.TabIndex = 13;
			this.btnRecursiveDLS.Text = "Recursive DLS";
			this.btnRecursiveDLS.Click += new System.EventHandler(this.btnRecursiveDLS_Click);
			// 
			// btnAStarMan
			// 
			this.btnAStarMan.Location = new System.Drawing.Point(464, 280);
			this.btnAStarMan.Name = "btnAStarMan";
			this.btnAStarMan.Size = new System.Drawing.Size(80, 48);
			this.btnAStarMan.TabIndex = 12;
			this.btnAStarMan.Text = "AStar Manhattan";
			this.btnAStarMan.Click += new System.EventHandler(this.btnAStarMan_Click);
			// 
			// btnGreedyBestFirst
			// 
			this.btnGreedyBestFirst.Location = new System.Drawing.Point(192, 280);
			this.btnGreedyBestFirst.Name = "btnGreedyBestFirst";
			this.btnGreedyBestFirst.Size = new System.Drawing.Size(80, 48);
			this.btnGreedyBestFirst.TabIndex = 11;
			this.btnGreedyBestFirst.Text = "Greedy Best First";
			this.btnGreedyBestFirst.Click += new System.EventHandler(this.btnGreedyBestFirst_Click);
			// 
			// btnAStar
			// 
			this.btnAStar.Location = new System.Drawing.Point(376, 280);
			this.btnAStar.Name = "btnAStar";
			this.btnAStar.Size = new System.Drawing.Size(80, 48);
			this.btnAStar.TabIndex = 10;
			this.btnAStar.Text = "AStar";
			this.btnAStar.Click += new System.EventHandler(this.btnAStar_Click);
			// 
			// btnGreedyBestFirstMan
			// 
			this.btnGreedyBestFirstMan.Location = new System.Drawing.Point(280, 280);
			this.btnGreedyBestFirstMan.Name = "btnGreedyBestFirstMan";
			this.btnGreedyBestFirstMan.Size = new System.Drawing.Size(88, 48);
			this.btnGreedyBestFirstMan.TabIndex = 9;
			this.btnGreedyBestFirstMan.Text = "Greedy Best First Manhattan";
			this.btnGreedyBestFirstMan.Click += new System.EventHandler(this.btnGreedyBestFirstMan_Click);
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(8, 0);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.textBox1.Size = new System.Drawing.Size(616, 272);
			this.textBox1.TabIndex = 7;
			this.textBox1.Text = "Eight Puzzle Demo";
			// 
			// btnSimulatedAnnealing
			// 
			this.btnSimulatedAnnealing.Location = new System.Drawing.Point(552, 280);
			this.btnSimulatedAnnealing.Name = "btnSimulatedAnnealing";
			this.btnSimulatedAnnealing.Size = new System.Drawing.Size(80, 48);
			this.btnSimulatedAnnealing.TabIndex = 14;
			this.btnSimulatedAnnealing.Text = "Simulated Annealing";
			this.btnSimulatedAnnealing.Click += new System.EventHandler(this.btnSimulatedAnnealing_Click);
			// 
			// btnIDLS
			// 
			this.btnIDLS.Location = new System.Drawing.Point(104, 280);
			this.btnIDLS.Name = "btnIDLS";
			this.btnIDLS.Size = new System.Drawing.Size(88, 48);
			this.btnIDLS.TabIndex = 15;
			this.btnIDLS.Text = "Iterative DLS";
			this.btnIDLS.Click += new System.EventHandler(this.btnIDLS_Click);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 15);
			this.ClientSize = new System.Drawing.Size(640, 336);
			this.Controls.Add(this.btnIDLS);
			this.Controls.Add(this.btnSimulatedAnnealing);
			this.Controls.Add(this.btnRecursiveDLS);
			this.Controls.Add(this.btnAStarMan);
			this.Controls.Add(this.btnGreedyBestFirst);
			this.Controls.Add(this.btnAStar);
			this.Controls.Add(this.btnGreedyBestFirstMan);
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

		static EightPuzzleBoard boardWithThreeMoveSolution = new EightPuzzleBoard(
			new int[] { 1, 2, 5, 3, 4, 0, 6, 7, 8 });

		static EightPuzzleBoard random1 = new EightPuzzleBoard(new int[] { 1, 4, 2,
																			 7, 5, 8, 3, 0, 6 });
	
		static EightPuzzleBoard extreme = new EightPuzzleBoard(new int[] { 0,8, 7, 6,
																			 5, 4, 3, 2, 1 });

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

		private void btnRecursiveDLS_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "EightPuzzleDemo recursive DLS-->" + System.Environment.NewLine;
			Problem problem = new Problem(random1,
				new EightPuzzleSuccessorFunction(),
				new EightPuzzleGoalTest());
			Search search = new DepthLimitedSearch(9);
			SearchAgent agent = new SearchAgent(problem, search);
			printActions(agent.getActions());
			printInstrumentation(agent.getInstrumentation());
		}

		private void btnIDLS_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "EightPuzzleDemo Iterative DLS-->" + System.Environment.NewLine;
			Problem problem = new Problem(random1,
				new EightPuzzleSuccessorFunction(),
				new EightPuzzleGoalTest());
			Search search = new IterativeDeepeningSearch();
			SearchAgent agent = new SearchAgent(problem, search);
			printActions(agent.getActions());
			printInstrumentation(agent.getInstrumentation());
		}

		private void btnGreedyBestFirst_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "Greedy Best First Search (MisplacedTileHeuristic-->" + System.Environment.NewLine;
			Problem problem = new Problem(boardWithThreeMoveSolution,
				new EightPuzzleSuccessorFunction(),
				new EightPuzzleGoalTest(),
				new MisplacedTilleHeuristicFunction());
			Search search = new GreedyBestFirstSearch(new GraphSearch());
			SearchAgent agent = new SearchAgent(problem, search);
			printActions(agent.getActions());
			printInstrumentation(agent.getInstrumentation());
		}

		private void btnGreedyBestFirstMan_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "EightPuzzleDemo Greedy Best First Search (ManhattanHeursitic)-->" + System.Environment.NewLine;
			Problem problem = new Problem(boardWithThreeMoveSolution,
				new EightPuzzleSuccessorFunction(),
				new EightPuzzleGoalTest(), new ManhattanHeuristicFunction());
			Search search = new GreedyBestFirstSearch(new GraphSearch());
			SearchAgent agent = new SearchAgent(problem, search);
			printActions(agent.getActions());
			printInstrumentation(agent.getInstrumentation());
		}

		private void btnAStar_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "EightPuzzleDemo AStar Search (MisplacedTileHeursitic)-->" + System.Environment.NewLine;

			Problem problem = new Problem(random1,
				new EightPuzzleSuccessorFunction(),
				new EightPuzzleGoalTest(),
				new MisplacedTilleHeuristicFunction());
			Search search = new AStarSearch(new GraphSearch());
			SearchAgent agent = new SearchAgent(problem, search);
			printActions(agent.getActions());
			printInstrumentation(agent.getInstrumentation());
		}

		private void btnAStarMan_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "EightPuzzleDemo AStar Search (ManhattanHeursitic)-->" + System.Environment.NewLine;
			Problem problem = new Problem(random1,
				new EightPuzzleSuccessorFunction(),
				new EightPuzzleGoalTest(), new ManhattanHeuristicFunction());
			Search search = new AStarSearch(new GraphSearch());
			SearchAgent agent = new SearchAgent(problem, search);
			printActions(agent.getActions());
			printInstrumentation(agent.getInstrumentation());
		}

		private void btnSimulatedAnnealing_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "EightPuzzleDemo Simulated Annealing  Search -->" + System.Environment.NewLine;
			Problem problem = new Problem(random1,
				new EightPuzzleSuccessorFunction(),
				new EightPuzzleGoalTest(), new ManhattanHeuristicFunction());
			Search search = new SimulatedAnnealingSearch();
			SearchAgent agent = new SearchAgent(problem, search);
			printActions(agent.getActions());
			printInstrumentation(agent.getInstrumentation());
		}


	}
}
