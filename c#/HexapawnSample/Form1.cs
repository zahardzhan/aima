using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using aima.games;

namespace HexapawnSample
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Button btnHexMiniMax;
		private System.Windows.Forms.Button btnHexAlphaBeta;
		private System.Windows.Forms.Button btnMiniMaxOctapawn;
		private System.Windows.Forms.Button btnAlphaBetaOctapawn;
		private System.Windows.Forms.Button btnAlphaBetaDecapawn;
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
			this.btnHexMiniMax = new System.Windows.Forms.Button();
			this.btnHexAlphaBeta = new System.Windows.Forms.Button();
			this.btnMiniMaxOctapawn = new System.Windows.Forms.Button();
			this.btnAlphaBetaOctapawn = new System.Windows.Forms.Button();
			this.btnAlphaBetaDecapawn = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// textBox1
			// 
			this.textBox1.Font = new System.Drawing.Font("Courier New", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.textBox1.Location = new System.Drawing.Point(24, 16);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.textBox1.Size = new System.Drawing.Size(512, 280);
			this.textBox1.TabIndex = 0;
			this.textBox1.Text = "Hexapawn!";
			// 
			// btnHexMiniMax
			// 
			this.btnHexMiniMax.Location = new System.Drawing.Point(32, 304);
			this.btnHexMiniMax.Name = "btnHexMiniMax";
			this.btnHexMiniMax.Size = new System.Drawing.Size(80, 40);
			this.btnHexMiniMax.TabIndex = 1;
			this.btnHexMiniMax.Text = "MiniMax Hexapawn";
			this.btnHexMiniMax.Click += new System.EventHandler(this.btnHexMiniMax_Click);
			// 
			// btnHexAlphaBeta
			// 
			this.btnHexAlphaBeta.Location = new System.Drawing.Point(120, 304);
			this.btnHexAlphaBeta.Name = "btnHexAlphaBeta";
			this.btnHexAlphaBeta.Size = new System.Drawing.Size(75, 40);
			this.btnHexAlphaBeta.TabIndex = 2;
			this.btnHexAlphaBeta.Text = "AlphaBeta Hexapawn";
			this.btnHexAlphaBeta.Click += new System.EventHandler(this.btnHexAlphaBeta_Click);
			// 
			// btnMiniMaxOctapawn
			// 
			this.btnMiniMaxOctapawn.Location = new System.Drawing.Point(248, 304);
			this.btnMiniMaxOctapawn.Name = "btnMiniMaxOctapawn";
			this.btnMiniMaxOctapawn.Size = new System.Drawing.Size(75, 40);
			this.btnMiniMaxOctapawn.TabIndex = 3;
			this.btnMiniMaxOctapawn.Text = "MiniMax Octapawn";
			this.btnMiniMaxOctapawn.Click += new System.EventHandler(this.btnMiniMaxOctapawn_Click);
			// 
			// btnAlphaBetaOctapawn
			// 
			this.btnAlphaBetaOctapawn.Location = new System.Drawing.Point(336, 304);
			this.btnAlphaBetaOctapawn.Name = "btnAlphaBetaOctapawn";
			this.btnAlphaBetaOctapawn.Size = new System.Drawing.Size(75, 40);
			this.btnAlphaBetaOctapawn.TabIndex = 4;
			this.btnAlphaBetaOctapawn.Text = "AlphaBeta Octapawn";
			this.btnAlphaBetaOctapawn.Click += new System.EventHandler(this.btnAlphaBetaOctapawn_Click);
			// 
			// btnAlphaBetaDecapawn
			// 
			this.btnAlphaBetaDecapawn.Location = new System.Drawing.Point(448, 304);
			this.btnAlphaBetaDecapawn.Name = "btnAlphaBetaDecapawn";
			this.btnAlphaBetaDecapawn.Size = new System.Drawing.Size(80, 40);
			this.btnAlphaBetaDecapawn.TabIndex = 5;
			this.btnAlphaBetaDecapawn.Text = "AlphaBeta Decapawn";
			this.btnAlphaBetaDecapawn.Click += new System.EventHandler(this.btnAlphaBetaDecapawn_Click);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 15);
			this.ClientSize = new System.Drawing.Size(560, 352);
			this.Controls.Add(this.btnAlphaBetaDecapawn);
			this.Controls.Add(this.btnAlphaBetaOctapawn);
			this.Controls.Add(this.btnMiniMaxOctapawn);
			this.Controls.Add(this.btnHexAlphaBeta);
			this.Controls.Add(this.btnHexMiniMax);
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

		private void btnHexMiniMax_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "MINI MAX Hexapawn";
			this.textBox1.Text += System.Environment.NewLine;
		
			Hexapawn t3 = new Hexapawn();
			while (!(t3.hasEnded())) 
			{
				this.textBox1.Text += (System.Environment.NewLine + t3.getPlayerToMove(t3.getState()) + " playing");
				this.textBox1.Text += System.Environment.NewLine;
				t3.makeMiniMaxMove();
				GameState presentState = t3.getState();
				HexapawnBoard board = t3.getBoard(presentState);
				this.textBox1.Text += System.Environment.NewLine;
				this.textBox1.Text += board.ToString();
				this.textBox1.Refresh();
				this.Refresh();
			
			}
			this.textBox1.Text += "Mini MAX Hexapawn DEMO done";
		}

		private void btnHexAlphaBeta_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "ALPHA BETA Hexapawn";
			this.textBox1.Text +=  System.Environment.NewLine;
			Hexapawn t4 = new Hexapawn();
			while (!(t4.hasEnded())) 
			{
				this.textBox1.Text += (System.Environment.NewLine+t4.getPlayerToMove(t4.getState())
					+ "  playing ... ");

				t4.makeAlphaBetaMove();
				GameState presentState = t4.getState();
				HexapawnBoard board = t4.getBoard(presentState);
				this.textBox1.Text += System.Environment.NewLine;
				this.textBox1.Text += board.ToString();
			}
			this.textBox1.Text += "ALPHA BETA Hexapawn DEMO done";
		}

		private void btnMiniMaxOctapawn_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "MINI MAX Octapawn";
			this.textBox1.Text += System.Environment.NewLine;
		
			Octapawn t3 = new Octapawn();
			while (!(t3.hasEnded())) 
			{
				this.textBox1.Text += (System.Environment.NewLine + t3.getPlayerToMove(t3.getState()) + " playing");
				this.textBox1.Text += System.Environment.NewLine;
				t3.makeMiniMaxMove();
				GameState presentState = t3.getState();
				OctapawnBoard board = t3.getBoard(presentState);
				this.textBox1.Text += System.Environment.NewLine;
				this.textBox1.Text += board.ToString();
				this.textBox1.Refresh();
				this.Refresh();
			
			}
			this.textBox1.Text += "Mini MAX Octapawn DEMO done";
		}

		private void btnAlphaBetaOctapawn_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "ALPHA BETA Octapawn ";
			this.textBox1.Text +=  System.Environment.NewLine;
			Octapawn t4 = new Octapawn();
			while (!(t4.hasEnded())) 
			{
				this.textBox1.Text += (System.Environment.NewLine+t4.getPlayerToMove(t4.getState())
					+ "  playing ... ");

				t4.makeAlphaBetaMove();
				GameState presentState = t4.getState();
				OctapawnBoard board = t4.getBoard(presentState);
				this.textBox1.Text += System.Environment.NewLine;
				this.textBox1.Text += board.ToString();
				this.textBox1.Refresh();
				this.Refresh();
			}
			this.textBox1.Text += "ALPHA BETA Octapawn DEMO done";
		}

		private void btnAlphaBetaDecapawn_Click(object sender, System.EventArgs e)
		{
			this.textBox1.Text = "ALPHA BETA Decapawn ";
			this.textBox1.Text +=  System.Environment.NewLine;
			Decapawn t4 = new Decapawn();
			while (!(t4.hasEnded())) 
			{
				this.textBox1.Text += (System.Environment.NewLine+t4.getPlayerToMove(t4.getState())
					+ "  playing ... ");

				t4.makeAlphaBetaMove();
				GameState presentState = t4.getState();
				DecapawnBoard board = t4.getBoard(presentState);
				this.textBox1.Text += System.Environment.NewLine;
				this.textBox1.Text += board.ToString();
				this.textBox1.Refresh();
				this.Refresh();
				
			}
			this.textBox1.Text += "ALPHA BETA Decapawn DEMO done";
		}
	}
}
