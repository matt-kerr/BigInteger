// Matthew Kerr
//
// Addition uses the method at https://www.mathsisfun.com/numbers/addition-column.html
// Subtraction uses the method at https://www.mathsisfun.com/numbers/subtraction-quick.html
// Multiplication uses the method at https://www.mathsisfun.com/numbers/multiplication-long.html

#include <sstream>
#include "biginteger.h"
using namespace std;

BigInteger::BigInteger()
{
	size = 1;
	sign = 1;
	nums = new int[1];
	nums[0] = 0;
}

BigInteger::BigInteger(const int& input)
{
	string temp;
	stringstream out;
	out << input;
	temp = out.str();
	
	this->size = (int) temp.length();
	this->sign = (temp[0] == '-' ? -1 : 1);
	this->nums = new int[this->size];
	if (temp[0] == '-')
	{
		temp[0] = '0';
	}
	for (int i = 0; i < this->size; i++)
	{
		this->nums[i] = temp[i] - '0';
	}
	stripZeros();
}

BigInteger::BigInteger(const string input)
{
	string temp = input;
	if (temp[0] == '-')
	{
		sign = -1;
		temp = temp.substr(1);
	}
	else
	{
		sign = 1;
	}
	size = temp.size();
	nums = new int[size];
	for (int i = 0; i < size; i++)
	{
		nums[i] = temp[i] - '0';
	}
	stripZeros();
}

BigInteger::BigInteger(const BigInteger& other)
{
	this->size = 0;
	this->sign = 0;
	this->nums = NULL;
	*this = other;
}

BigInteger& BigInteger::operator=(const BigInteger& orig)
{
	this->size = orig.size;
	this->sign = orig.sign;
	this->nums = new int[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->nums[i] = orig.nums[i];
	}
	return *this;
}

BigInteger& BigInteger::operator=(const int& orig)
{
	string temp;
	stringstream out;
	out << orig;
	temp = out.str();
	
	this->size = (int) temp.length();
	this->sign = (temp[0] == '-' ? -1 : 1);
	this->nums = new int[this->size];
	if (temp[0] == '-')
	{
		temp[0] = '0';
	}
	for (int i = 0; i < this->size; i++)
	{
		this->nums[i] = temp[i] - '0';
	}
	stripZeros();
	return *this;
}

BigInteger::~BigInteger()
{
	delete nums;
}

BigInteger BigInteger::operator+(const BigInteger& rhs) const
{
	BigInteger result;
	BigInteger top = *this;
	BigInteger bot = rhs;
	// both positive or both negative, do addition
	if (top.sign == bot.sign)
	{
		result.sign = top.sign;
		int new_size = 0;
		int curr_total = 0;
		int carry = 0;
		int final_carry = 0;
		int top_pos = 0;
		int bot_pos = 0;
		int final_pos = 0;
		if (top.size > bot.size)
		{
			new_size = top.size;
		}
		else
		{
			new_size = bot.size;
		}
		// first pass, determine final array size
		for (top_pos = top.size - 1, bot_pos = bot.size - 1; top_pos >= 0 || bot_pos >= 0; top_pos--, bot_pos--)
		{
			if (top_pos >= 0)
			{
				curr_total += top.nums[top_pos];
			}
			if (bot_pos >= 0)
			{
				curr_total += bot.nums[bot_pos];
			}
			curr_total += carry;
			if (curr_total > 9)
			{
				carry = 1;
			}
			else
			{
				carry = 0;
			}
			curr_total = 0;
		}
		if (carry == 1)
		{
			final_carry = 1;
		}
		result.size = new_size + carry;
		result.nums = new int[result.size];
		carry = 0;
		final_pos = result.size - 1;
		// second pass, remember the addition
		for (top_pos = top.size - 1, bot_pos = bot.size - 1; top_pos >= 0 || bot_pos >= 0; top_pos--, bot_pos--, final_pos--)
		{
			if (top_pos >= 0)
			{
				curr_total += top.nums[top_pos];
			}
			if (bot_pos >= 0)
			{
				curr_total += bot.nums[bot_pos];
			}
			curr_total += carry;
			result.nums[final_pos] = curr_total % 10;
			if (curr_total > 9)
			{
				carry = 1;
			}
			else
			{
				carry = 0;
			}
			curr_total = 0;
		}
		if (carry == 1)
		{
			result.nums[0] = 1;
		}			
	}
	// top positive, bot negative
	// do subtraction
	else if (top.sign == 1 && bot.sign == -1)
	{
		bot.sign = 1;
		if (top > bot)
		{
			result = top - bot;
			result.sign = 1;
		}
		else
		{
			result = bot - top;
			result.sign = -1;
		}
	}
	// top negative, bot positive
	// do subtraction
	else
	{
		top.sign = 1;
		if (top > bot)
		{
			result = top - bot;
			result.sign = -1;
		}
		else
		{
			result = bot - top;
			result.sign = 1;
		}
	}
	result.stripZeros();
	return result;
}

BigInteger BigInteger::operator-(const BigInteger& rhs) const
{
	// skip all the work if both numbers are equal
	if (*this == rhs)
	{
		return BigInteger("0");
	}
	BigInteger result;
	int nums_to_copy;
	// determine sign when subtracting 2 numbers with same sign
	if (this->sign == rhs.sign)
	{
		BigInteger top;
		BigInteger bot;
		// both positive, *this > rhs
		if ((*this > rhs) && (this->sign == 1))
		{
			nums_to_copy = rhs.size;
			top = *this;
			bot.size = top.size;
			bot.nums = new int[bot.size];
			for (int i = bot.size - 1; i >= 0; i--, nums_to_copy--)
			{
				if (nums_to_copy > 0)
				{
					bot.nums[i] = rhs.nums[nums_to_copy - 1];
				}
				else
				{
					bot.nums[i] = 0;
				}
			}
			result.sign = 1;
		}
		// both negative, *this < rhs
		else if ((*this < rhs) && (this->sign == -1))
		{
			nums_to_copy = rhs.size;
			top = *this;
			bot.size = top.size;
			bot.nums = new int[bot.size];
			for (int i = bot.size - 1; i >= 0; i--, nums_to_copy--)
			{
				if (nums_to_copy > 0)
				{
					bot.nums[i] = rhs.nums[nums_to_copy - 1];
				}
				else
				{
					bot.nums[i] = 0;
				}
			}
			result.sign = -1;
		}
		// both negative, *this > rhs
		else if ((*this > rhs) && (this->sign == -1))
		{
			nums_to_copy = this->size;
			top = rhs;
			bot.size = top.size;
			bot.nums = new int[bot.size];
			for (int i = bot.size - 1; i >= 0; i--, nums_to_copy--)
			{
				if (nums_to_copy > 0)
				{
					bot.nums[i] = this->nums[nums_to_copy - 1];
				}
				else
				{
					bot.nums[i] = 0;
				}
			}
			result.sign = 1;
		}
		// both positive, *this < rhs
		else
		{
			nums_to_copy = this->size;
			top = rhs;
			bot.size = top.size;
			bot.nums = new int[bot.size];
			for (int i = bot.size - 1; i >= 0; i--, nums_to_copy--)
			{
				if (nums_to_copy > 0)
				{
					bot.nums[i] = this->nums[nums_to_copy - 1];
				}
				else
				{
					bot.nums[i] = 0;
				}
			}
			result.sign = -1;
		}
		top.sign = 1;
		bot.sign = 1;	
		int new_size = 0;
		int curr_total = 0;
		int borrow = 0;
		int final_borrow = 0;
		int top_pos = 0;
		int bot_pos = 0;
		int borrow_pos = 0;
		int final_pos = 0;
		// determine largest array size needed for calculation
		if (top.size > bot.size)
		{
			result.size = top.size;
		}
		else
		{
			result.size = bot.size;
		}
		result.nums = new int[result.size];
		// do subtraction calculations
		for (top_pos = top.size - 1, bot_pos = bot.size - 1, final_pos = result.size - 1; top_pos >= 0; top_pos--, bot_pos--, final_pos--)
		{
			if (bot_pos >= 0)
			{
				if (top.nums[top_pos] == bot.nums[bot_pos])
				{
					result.nums[final_pos] = 0;
				}
				else if (top.nums[top_pos] > bot.nums[bot_pos])
				{
					result.nums[final_pos] = top.nums[top_pos] - bot.nums[bot_pos];
				}
				else
				{
					result.nums[final_pos] = 10 - (bot.nums[bot_pos] - top.nums[top_pos]);
					bot.nums[bot_pos - 1]++;
				}
				
			}
			else
			{
				result.nums[final_pos] = top.nums[top_pos];
			}
		}
	}
	// top positive, right negative
	// do addition
	else if ((this->sign == 1) && (rhs.sign == -1))
	{
		BigInteger top = *this;
		BigInteger bot = rhs; // !
		bot.sign = 1;
		result = top + bot;
		result.sign = 1;
	}
	// top negative, bot positive
	// do addition
	else
	{
		BigInteger top = *this;
		BigInteger bot = rhs;
		top.sign = 1;
		result = top + bot;
		result.sign = -1;
	}
	result.stripZeros();
	return result;
}

BigInteger BigInteger::operator*(const BigInteger& rhs) const
{
	BigInteger result;
	BigInteger top = *this;
	BigInteger bot = rhs;
	int result_sign = 0;
	if (top.sign == bot.sign)
	{
		result_sign = 1;
	}
	else
	{
		result_sign = -1;
	}
	top.sign = 1;
	bot.sign = 1;
	// make sure the bigger number is on top
	if (bot > top)
	{
		BigInteger temp = top;
		top = bot;
		bot = temp;
	}
	int num_values = bot.size;
	int length_values = top.size * 2;
	int values[num_values][length_values];
	for (int i = 0; i < num_values; i++)
	{
		for (int j = 0; j < length_values; j++)
		{
			values[i][j] = 0;
		}
	} 
	int top_pos = top.size - 1;
	int bot_pos = bot.size - 1;
	int result_pos = top.size - 1;
	int right_offset = top.size - 1;
	int result_size = top.size * 2;
	int x = 0;
	int values_index = 0;
	int offset = 0;
	int offset_start = length_values - 1;
	int temp_int = 0;
	int left_digit = 0;
	int right_digit = 0;
	int values_i = 0;
	string temp_string;
	for (int i = bot.size - 1; i >= 0; i--)
	{
		offset = offset_start;
		for (int j = top.size - 1; j >= 0; j--)
		{
			temp_int = top.nums[j] * bot.nums[i];
			values_index = offset;
			left_digit = temp_int / 10;
			right_digit = temp_int % 10;
			values[x][values_index] = values[x][values_index] + right_digit;
			// assign right digit
			if (values[x][values_index] > 9)
			{
				values[x][values_index] = values[x][values_index] % 10;
				values[x][values_index - 1]++;
			}
			values_index--;
			values[x][values_index] = values[x][values_index] + left_digit;
			// assign left digit, if it exists
			if (values[x][values_index] > 9)
			{
				values[x][values_index] = values[x][values_index] % 10;
				values[x][values_index - 1]++;
			}
			values_index--;
			// fix remaining numbers if they are broken
			while (values_index >= 0)
			{
				if (values[x][values_index] > 9)
				{
					values[x][values_index] = values[x][values_index] % 10;
					values[x][values_index - 1]++;
				}
				values_index--;
			}
			offset--;
		}
		x++;
		offset_start--;
	}
	// add all the numbers together
	for (int i = 0; i < num_values; i++)
	{
		temp_string = "";
		for (int j = 0; j < length_values; j++)
		{
			temp_string += values[i][j] + '0';
		}
		BigInteger temp_biginteger(temp_string);
		result = result + temp_biginteger;
	}
	result.sign = result_sign;
	return result;
}

bool BigInteger::operator<(const BigInteger& rhs) const
{
	// both are 0
	if (size == 1 && nums[0] == 0 && rhs.size == 1 && rhs.nums[0] == 0)
	{
		return false;
	}
	// this is negative, right side is positive
	else if (sign == -1 && rhs.sign == 1)
	{
		return true;
	}
	// this is positive, right side is negative
	else if (sign == 1 && rhs.sign == -1)
	{
		return false;
	}
	// both are positive
	else if (sign == 1 && rhs.sign == 1)
	{
		if (size < rhs.size)
		{
			return true;
		}
		else if (size > rhs.size)
		{
			return false;
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				if (nums[i] < rhs.nums[i])
				{
					return true;
				}
				else if (nums[i] > rhs.nums[i])
				{
					return false;
				}
				else if (nums[i] == rhs.nums[i])
				{
					// both are the same at this index, skip
				}
			}
		}
	}
	// both are negative
	else
	{
		if (size > rhs.size)
		{
			return true;
		}
		else if (size < rhs.size)
		{
			return false;
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				if (nums[i] > rhs.nums[i])
				{
					return true;
				}
				else if (nums[i] < rhs.nums[i])
				{
					return false;
				}
			}
		}
	}
	return false;
}

bool BigInteger::operator<=(const BigInteger& rhs) const
{
	return (*this < rhs) || (*this == rhs);
}

bool BigInteger::operator==(const BigInteger& rhs) const
{	
	if (sign != rhs.sign)
	{
		return false;
	}
	if (size != rhs.size)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (nums[i] != rhs.nums[i])
			{
				return false;
			}
		}
	}
	return true;
}

bool BigInteger::operator>(const BigInteger& rhs) const
{
	return ((!(*this < rhs)) && (*this != rhs));
}

bool BigInteger::operator>=(const BigInteger& rhs) const
{
	return (*this > rhs) || (*this == rhs);
}

istream& operator>>(istream& in, BigInteger& input)
{
	string temp;
	in >> temp;

	if (temp[0] == '-')
	{
		input.sign = -1;
		temp = temp.substr(1);
	}
	else
	{
		input.sign = 1;
	}
	input.size = temp.size();
	input.nums = new int[input.size];
	for (int i = 0; i < input.size; i++)
	{
		input.nums[i] = temp[i] - '0';
	}
	input.stripZeros();
	return in;
}

ostream& operator<<(ostream& out, const BigInteger& num)
{
	if (num.sign == -1)
	{
		cout << '-';
	}
	for (int i = 0; i < num.size; i++)
	{
		cout << num.nums[i];
	}
	return out;
}

void BigInteger::stripZeros()
{
	bool only_zeros = true;
	string temp = "";
	for (int i = 0; i < this->size; i++)
	{
		temp += this->nums[i] + '0';
	}
	for (int i = 0; i < this->size; i++)
	{
		if (this->nums[i] != 0)
		{
			only_zeros = false;
		}
	}
	if (only_zeros)
	{
		delete [] this->nums;
		this->nums = new int[1];
		this->nums[0] = 0;
		this->size = 1;
		this->sign = 1;
	}
	else
	{
		temp.erase(0, temp.find_first_not_of('0'));
		this->size = temp.size();
		this->nums = new int[this->size];
		for (int i = 0; i < this->size; i++)
		{
			this->nums[i] = temp[i] - '0';
		}
	}
}