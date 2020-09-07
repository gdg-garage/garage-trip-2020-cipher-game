#include "common.h"

#include <cage-core/image.h>
#include <cage-core/files.h>
#include <cage-core/math.h>
#include <cage-core/geometry.h>

namespace
{
	real hardEdge(real v)
	{
		return smootherstep(smootherstep(smootherstep(v)));
	}

	void addDotImg(Holder<Image> &img)
	{
		for (uint32 y = 0; y < 40; y++)
		{
			for (uint32 x = 0; x < 40; x++)
			{
				const real d = length(vec2(x, y) - vec2(20));
				const real op = hardEdge(clamp(1 - d * 0.1, 0, 1));
				img->set(x, y, interpolate(img->get3(x, y), vec3(0), op));
			}
		}
	}

	void addBordersImg(Holder<Image> &img, bool b[4])
	{
		for (uint32 y = 0; y < 40; y++)
		{
			for (uint32 x = 0; x < 40; x++)
			{
				real op = 0;
				if (b[0] && x < 10)
					op = 1;
				if (b[1] && x > 29)
					op = 1;
				if (b[2] && y < 10)
					op = 1;
				if (b[3] && y > 29)
					op = 1;
				img->set(x, y, interpolate(img->get3(x, y), vec3(0), op));
			}
		}
	}

	void addCrossImg(Holder<Image> &img, uint32 idx)
	{
		vec2 center;
		switch (idx)
		{
		case 0: center = vec2(20, 40); break;
		case 1: center = vec2(40, 20); break;
		case 2: center = vec2(0, 20); break;
		case 3: center = vec2(20, 0); break;
		default: CAGE_THROW_CRITICAL(Exception, "invalid cross idx");
		}
		const line l1 = makeLine(vec3(center + vec2(-1, -1), 0), vec3(center + vec2(1, 1), 0));
		const line l2 = makeLine(vec3(center + vec2(-1, 1), 0), vec3(center + vec2(1, -1), 0));
		for (uint32 y = 0; y < 40; y++)
		{
			for (uint32 x = 0; x < 40; x++)
			{
				const real d1 = distance(vec3(x, y, 0), l1);
				const real d2 = distance(vec3(x, y, 0), l2);
				const real d = min(d1, d2);
				const real op = hardEdge(clamp(1 - d * 0.1, 0, 1));
				img->set(x, y, interpolate(img->get3(x, y), vec3(0), op));
			}
		}
	}

	Holder<Image> genLetterImg(const char c_)
	{
		Holder<Image> img = newImage();
		img->initialize(40, 40, 3);
		img->fill(vec3(1));

		if (c_ <= 'R')
		{
			// grid
			const uint32 p = (c_ - 'A') % 9;
			const uint32 r = p / 3;
			const uint32 c = p % 3;
			bool b[4] = {
				c > 0,
				c < 2,
				r > 0,
				r < 2,
			};
			addBordersImg(img, b);
			if (c_ >= 'J')
				addDotImg(img);
		}
		else
		{
			// cross
			const uint32 p = (c_ - 'S') % 4;
			addCrossImg(img, p);
			if (c_ >= 'W')
				addDotImg(img);
		}

		return img;
	}

	void generateLetterImages(uint32 index)
	{
		for (char c = 'A'; c <= 'Z'; c++)
		{
			auto img = genLetterImg(c);
			img->exportFile(pathJoin(outputPath, stringizer() + index + "/" + string(&c, 1) + ".png"));
		}
	}

	std::string str(char c)
	{
		if (c >= 'A' && c <= 'Z')
			return std::string() + " <img src=\"1/" + c + ".png\" /> ";
		return std::string() + c;
	}
}

void cipher1()
{
	generateLetterImages(1);
	
	std::string i = readInput(1);
	i = replaceCzech(i);
	i = toUpper(i);

	std::string s;
	s.reserve(i.size() * 100);
	for (const char c : i)
		s += str(c);

	const std::string o = generateHeader(1) + s + generateFooter(1);
	writeOutput(1, o);
}

