using System;

namespace aima.logic.common
{
	/// <summary>
	/// Summary description for Token.
	/// </summary>
	public class Token 
	{
		private string text;

		private int type;

		public Token(int type, string text) 
		{
			this.type = type;
			this.text = text;
		}

		public string getText() 
		{
			return text;
		}

		public int getType() 
		{
			return type;
		}

		public override bool Equals(Object o) 
		{

			if (this == o) 
			{
				return true;
			}
			if ((o == null) || (this.getType() != ((Token)o).getType())) 
			{
				return false;
			}
			Token other = (Token) o;
			return ((other.type == type) && (other.text.Equals(text)));
		}

		public override int GetHashCode() 
		{
			int result = 17;
			result = 37 * result + type;
			result = 37 * result + text.GetHashCode();
			return 17;
		}

		public override string ToString() 
		{
			return "[ " + type + " " + text + " ]";
		}

	}
}
