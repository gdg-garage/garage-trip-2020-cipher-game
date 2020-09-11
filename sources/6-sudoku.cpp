#include "common.h"

#include <cage-core/image.h>
#include <cage-core/math.h>
#include <cage-core/files.h>
#include <cage-core/memoryBuffer.h>

#include <algorithm>
#include <utility>

namespace
{
	constexpr const char *configTask = R"foo(
_6_5__
___4__
_3614_
_4__36
_513__
__465_
)foo";

	constexpr const char *configSolution = R"foo(
462513
513462
236145
145236
651324
324651
)foo";

	std::string loadSudoku(std::string s)
	{
		replace(s, "\n", "");
		replace(s, "\r", "");
		replace(s, " ", "");
		replace(s, "_", " ");
		if (s.length() != 36)
			CAGE_THROW_ERROR(Exception, "invalid sudoku string length");
		return s;
	}

	uint32 subgrid(uint32 x, uint32 y, bool transpose)
	{
		if (transpose)
			std::swap(x, y);
		x /= 3;
		y /= 2;
		return y * 3 + x;
	}

	std::string sudokuToHtml(const std::string &cells, bool transposeBackground)
	{
		CAGE_ASSERT(cells.size() == 36);

		std::string s = "<table>\n";
		for (uint32 y = 0; y < 6; y++)
		{
			s += "<tr>";
			for (uint32 x = 0; x < 6; x++)
			{
				if (subgrid(x, y, transposeBackground) % 2 == 0)
					s += "<td class=\"odd\">";
				else
					s += "<td>";
				s += cells[y * 6 + x];
			}
			s += "</tr>\n";
		}
		return s + "</table>\n";
	}

	std::string rotateSudoku(const std::string &cells)
	{
		CAGE_ASSERT(cells.size() == 36);
		std::string s;
		s.reserve(36);
		for (uint32 y = 0; y < 6; y++)
		{
			for (uint32 x = 0; x < 6; x++)
			{
				s += cells[(5 - x) * 6 + y];
			}
		}
		return s;
	}

	bool validateStencil(const std::string &cells, const char k)
	{
		CAGE_ASSERT(cells.size() == 36);
		std::string t = cells;
		bool visited[36] = {};
		for (uint32 r = 0; r < 4; r++)
		{
			for (uint32 i = 0; i < 36; i++)
			{
				if (t[i] == k)
				{
					if (visited[i])
						return false;
					visited[i] = true;
				}
			}
			t = rotateSudoku(t);
		}
		return true;
	}

	std::string strToTableWithStencil(const std::string &stencil, const char key, std::string &text)
	{
		CAGE_ASSERT(validateStencil(stencil, key));
		std::string s;
		s.resize(36, ' ');
		std::string st = stencil;
		for (uint32 r = 0; r < 4; r++)
		{
			for (uint32 i = 0; i < 36 && !text.empty(); i++)
			{
				if (st[i] == key)
				{
					CAGE_ASSERT(s[i] == ' ');
					s[i] = text[0];
					text.erase(text.begin());
				}
			}
			st = rotateSudoku(st);
		}
		return s;
	}

	void validateSudoku(const std::string &task, const std::string &solution)
	{
		CAGE_ASSERT(task.size() == 36);
		CAGE_ASSERT(solution.size() == 36);
		char c[6][6] = {};
		for (uint32 i = 0; i < 36; i++)
		{
			if (task[i] != ' ' && task[i] != solution[i])
				CAGE_THROW_ERROR(Exception, "incompatible task and solution");
			c[i / 6][i % 6] = solution[i];
		}
		for (uint32 y = 0; y < 6; y++)
		{
			for (uint32 x = 0; x < 6; x++)
			{
				if (c[y][x] == c[y][0] && x != 0)
					CAGE_THROW_ERROR(Exception, "duplicate value in a row");
				if (c[y][x] == c[0][x] && y != 0)
					CAGE_THROW_ERROR(Exception, "duplicate value in a column");
			}
		}
	}

	std::string stencilKeys(const std::string &cells)
	{
		std::string s;
		for (uint32 i = 0; i < 6; i++)
		{
			if (validateStencil(cells, cells[i]))
				s += cells[i];
		}
		return s;
	}
}

void cipher6()
{
	constexpr uint32 cypherIndex = 6;

	const std::string task = loadSudoku(configTask);
	const std::string solution = loadSudoku(configSolution);
	validateSudoku(task, solution);
	std::string keys = stencilKeys(solution);
	if (keys.empty())
		CAGE_THROW_ERROR(Exception, "sudoku cannot be used as a stencil");
	std::sort(keys.begin(), keys.end());

	std::string i = readInput(cypherIndex);
	i = replaceLfToSpaces(i);
	i = replaceCzech(i);
	i = toUpper(i);

	std::string s;
	uint32 ki = 0;
	while (!i.empty())
	{
		const char key = keys[ki % keys.size()];
		const std::string t = strToTableWithStencil(solution, key, i);
		s += sudokuToHtml(t, (ki % 2) == 1);
		s += "\n";
		ki++;
	}
	s += sudokuToHtml(task, false);

	std::string style = R"foo(
<style>
table
{
	border: 1px solid black;
	display: inline-block;
	margin: 2px;
}
td
{
	border: 1px solid gray;
	width: 2em;
	height: 2em;
	text-align: center;
	vertical-align: middle;
}
.odd
{
	background-color: Gainsboro;
}
</style>
)foo";

	const std::string o = generateHeader(cypherIndex) + style + s + generateFooter(cypherIndex);
	writeOutput(cypherIndex, o);
}

