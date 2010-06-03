using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using aima.games;


namespace TicTacToeSample
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Button btnAlphaBeta;
		private System.Windows.Forms.Button btnMiniMax;
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
			this.btnAlphaBeta = new System.Windows.Forms.Button();
			this.btnMiniMax = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(8, 16);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.textBox1.Size = new System.Drawing.Size(448, 240);
			this.textBox1.TabIndex = 0;
			this.textBox1.Text = "";
			// 
			// btnAlphaBeta
			// 
			this.btnAlphaBeta.Location = new System.Drawing.Point(40, 264);
			this.btnAlphaBeta.Name = "btnAlphaBeta";
			this.btnAlphaBeta.Size = new System.Drawing.Size(104, 40);
			this.btnAlphaBeta.TabIndex = 1;
			this.btnAlphaBeta.Text = "AlphaBeta Demo";
			this.btnAlphaBeta.Click += new System.EventHandler(this.btnAlphaBeta_Click);
			// 
			// btnMiniMax
			// 
			this.btnMiniMax.Location = new System.Drawing.Point(304, 264);
			this.btnMiniMax.Name = "btnMiniMax";
			this.btnMiniMax.Size = new System.Drawing.Size(96, 40);
			this.btnMiniMax.TabIndex = 2;
			this.btnMiniMax.Text = "MiniMax Demo";
			this.btnMiniMax.Click += new System.EventHandler(this.btnMiniMax_Click);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 15);
			this.ClientSize = new System.Drawing.Size(472, 320);
			this.Controls.Add(this.btnMiniMax);
			this.Controls.Add(this.btnAlphaBeta);
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


		private void btnAlphaBeta_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "ALPHA BETA ";
			this.textBox1.Text +=  System.Environment.NewLine;
			TicTacToe t4 = new TicTacToe();
			while (!(t4.hasEnded())) {
				this.textBox1.Text += (System.Environment.NewLine+t4.getPlayerToMove(t4.getState())
						+ "  playing ... ");

				t4.makeAlphaBetaMove();
				GameState presentState = t4.getState();
				TicTacToeBoard board = t4.getBoard(presentState);
				this.textBox1.Text += System.Environment.NewLine;
				this.textBox1.Text += board.ToString();
			}
			this.textBox1.Text += "ALPHA BETA DEMO done";
		}

		private void btnMiniMax_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "MINI MAX ";
			this.textBox1.Text += System.Environment.NewLine;
		
			TicTacToe t3 = new TicTacToe();
			while (!(t3.hasEnded())) 
			{
				this.textBox1.Text += (System.Environment.NewLine + t3.getPlayerToMove(t3.getState()) + " playing");
				this.textBox1.Text += System.Environment.NewLine;
				t3.makeMiniMaxMove();
				GameState presentState = t3.getState();
				TicTacToeBoard board = t3.getBoard(presentState);
				this.textBox1.Text += System.Environment.NewLine;
				this.textBox1.Text += board.ToString();
			
			}
			this.textBox1.Text += "Mini MAX DEMO done";
		}

	}
}
