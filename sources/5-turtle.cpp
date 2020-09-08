#include "common.h"

#include <cage-core/image.h>
#include <cage-core/math.h>
#include <cage-core/files.h>

namespace
{
	template<class Callable>
	void evaluateProgram(const std::string &program, Callable callable)
	{
		uint32 len = 0;
		char other = 'c';
		for (const char c : program)
		{
			if (c >= '1' && c <= '9')
				len = c - '0';
			else if (c >= 'a' && c <= 'z')
			{
				for (uint32 i = 0; i < len; i++)
				{
					switch (c)
					{
					case 's': callable(other, ivec2(0, -1)); break;
					case 'j': callable(other, ivec2(0, 1)); break;
					case 'v': callable(other, ivec2(1, 0)); break;
					case 'z': callable(other, ivec2(-1, 0)); break;
					default: other = c; break;
					}
				}
			}
		}
	}

	void findResolution(const std::string &program, ivec2 &resolution, ivec2 &start)
	{
		ivec2 a, b, pos;
		evaluateProgram(program, [&](const char other, const ivec2 &move) {
			pos += move;
			a = min(a, pos);
			b = max(b, pos);
			});
		resolution = b - a + ivec2(10);
		start = -a + ivec2(5);
	}

	Holder<Image> renderProgram(const std::string &program)
	{
		Holder<Image> img = newImage();
		ivec2 resolution, start;
		findResolution(program, resolution, start);
		img->initialize(resolution[0] * 2, resolution[1] * 2, 3);
		start *= 2;
		img->fill(vec3(1));
		evaluateProgram(program, [&](const char other, const ivec2 &move) {
			if (other == 'c')
			{
				img->set(start[0], start[1], vec3(0));
				start += move;
				img->set(start[0], start[1], vec3(0));
				start += move;
				img->set(start[0], start[1], vec3(0));
			}
			else
				start += move * 2;
			});
		return img;
	}

	std::string turtleChar(const char c)
	{
		switch (c)
		{
		case 'a': return "4s2vjzvjb1vc";
		case 'b': return "1v4s1z2vj1zv2j1zb2vc";
		case 'c': return "2vbzc4s2vb1v4jc";
		case 'd': return "1v4s1z2v4j1zb2vc";
		case 'e': return "2vz2s1vz2s2vb1v4jc";
		case 'f': return "2s1vz2s2vb1v4jc";
		case 'g': return "4s2vb2jc1zv2jzb3vc";
		case 'h': return "4sb2vc2jzvjb1vc";
		case 'i': return "2v1z4s1z2vb4j1vc";
		case 'j': return "2sjv4sjb1vc";
		case 'k': return "4sb2vc1jzjzvjvjbvc";
		case 'l': return "4sj2vb1vc";
		case 'm': return "4s1vjsv4jb1vc";
		case 'n': return "4s1v4j1v4sbj1vc";
		case 'o': return "4s2v4j2z3bvc";
		case 'p': return "4s2vjzb3v2jc";
		case 'q': return "4s2v4j1szb2v1jc";
		case 'r': return "4s2vjz1vjvjb1vc";
		case 's': return "2vszsvb1v4jc";
		case 't': return "b1vc4s1z2vb1v4jc";
		case 'u': return "4sj2v4sjb1vc";
		case 'v': return "4s3j1vsv2sbv4jc";
		case 'w': return "4sj1vsjv4sj1bvc";
		case 'x': return "1sv2s1zsb2vc1jz2j1vjb1vc";
		case 'y': return "b1vc2s1z2sbvcj1zb2vjc";
		case 'z': return "4bsc2v1jz2j1zj2vb1vc";
		case ' ': return "b2vc";
		default: return std::string(&c, 1);
		}
	}

	std::string turtleWord(const std::string &word)
	{
		std::string s;
		for (const char c : word)
			s += turtleChar(c);
		return s;
	}

	std::string splitLongWords(const std::string &i, uint32 maxWord = 10)
	{
		std::string s;
		s.reserve(i.size() * (maxWord + 1) / maxWord + 5);
		uint32 l = 1;
		for (const char c : i)
		{
			s += c;
			if (c == ' ')
				l = 1;
			else if (l == maxWord)
			{
				l = 1;
				s += " ";
			}
			else
				l++;
		}
		return s;
	}
}

void cipher5()
{
	constexpr uint32 cypherIndex = 5;

	std::string i = readInput(cypherIndex);
	i = replaceLfToSpaces(i);
	i = replaceCzech(i);
	i = toLower(i);

	std::string s = turtleWord(i);
	s = splitLongWords(s);

	Holder<Image> img = renderProgram(s);
	img->exportFile(pathJoin(outputPath, stringizer() + cypherIndex + "/intermediate.png"));

	const std::string o = generateHeader(cypherIndex) + s + generateFooter(cypherIndex);
	writeOutput(cypherIndex, o);
}

