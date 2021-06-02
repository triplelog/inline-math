#include "~/inline-math/cLaTeXMath-master/src/config.h"

#include "latex.h"
#include "platform/cairo/graphic_cairo.h"
#include "samples.h"


using namespace tex;


class Headless {
public:
  string _outputDir;
  string _samplesFile;
  string _prefix;

  string _input;
  string _outputFile;

  float _textSize = 20.f;
  color _foreground = BLACK;
  color _background = TRANSPARENT;
  float _padding = 10.f;
  float _maxWidth = 720.f;

  void generateSingle(const wstring& code, const string& file) const {
    auto r = LaTeX::parse(code, _maxWidth, _textSize, _textSize / 3.f, _foreground);
    const float w = r->getWidth() + _padding * 2;
    const float h = r->getHeight() + _padding * 2;
    auto surface = Cairo::SvgSurface::create(file, w, h);
    auto context = Cairo::Context::create(surface);
    Graphics2D_cairo g2(context);
    if (!isTransparent(_background)) {
      g2.setColor(_background);
      g2.fillRect(0, 0, w, h);
    }
    r->draw(g2, _padding, _padding);
    delete r;
  }

  int runBatch() const {
    if (_outputDir.empty()) {
      __print(ANSI_COLOR_RED "Error: the option '-outputdir' must be specified\n" ANSI_RESET);
      return 1;
    }
    Samples samples(_samplesFile);
    if (samples.count() == 0) return 1;
    for (int i = 0; i < samples.count(); i++) {
      generateSingle(samples.next(), _outputDir + "/" + _prefix + tostring(i) + ".svg");
    }
    return 0;
  }

  int runSingle() const {
    if (_outputFile.empty()) {
      __print(ANSI_COLOR_RED "Error: the option '-output' must be specified\n" ANSI_RESET);
      return 1;
    }
    wstring code = utf82wide(_input);
    generateSingle(code, _outputFile);
    return 0;
  }

  int run() {
    if (_textSize <= 0.f) _textSize = 20.f;
    if (isTransparent(_foreground)) _foreground = BLACK;
    if (_maxWidth <= 0.f) _maxWidth = 720.f;
    if (!_input.empty()) return runSingle();
    return runBatch();
  }
};

#include "atom/atom_basic.h"

int runHeadless(const vector<string>& opts) {
  Headless h;
  for (const auto& x : opts) {
    if (startswith(x, "-outputdir")) {
      h._outputDir = x.substr(x.find('=') + 1);
    } else if (startswith(x, "-samples")) {
      h._samplesFile = x.substr(x.find('=') + 1);
    } else if (startswith(x, "-prefix")) {
      h._prefix = x.substr(x.find('=') + 1);
    } else if (startswith(x, "-textsize")) {
      auto str = x.substr(x.find('=') + 1);
      valueof(str, h._textSize);
    } else if (startswith(x, "-foreground")) {
      auto str = x.substr(x.find('=') + 1);
      h._foreground = tex::ColorAtom::getColor(str);
    } else if (startswith(x, "-background")) {
      auto str = x.substr(x.find('=') + 1);
      h._background = tex::ColorAtom::getColor(str);
    } else if (startswith(x, "-input")) {
      h._input = x.substr(x.find('=') + 1);
    } else if (startswith(x, "-output")) {
      h._outputFile = x.substr(x.find('=') + 1);
    } else if (startswith(x, "-padding")) {
      auto str = x.substr(x.find('=') + 1);
      valueof(str, h._padding);
    } else if (startswith(x, "-maxwidth")) {
      auto str = x.substr(x.find('=') + 1);
      valueof(str, h._maxWidth);
    }
  }

  return h.run();
}



int runHelp() {
#define B ANSI_BOLD
#define R ANSI_RESET
  const char* msg =
    "Application to parse and display LaTeX code. The application will run with the headless\n"
    "mode if the option '-headless' has given, otherwise, it will run with the GUI mode.\n\n" B
    "NOTICE\n" R
    "  If both '-outputdir' and '-input' are specified, the '-input' option wins.\n\n" B
    "  COMMON OPTIONS\n\n"
    "  -h\n" R
    "      show usages and exit\n\n" B
    "  -headless\n" R
    "      run the application with the headless mode (no GUI), that converts the input LaTeX\n"
    "      code into SVG file\n\n" B
    "  -textsize=[VALUE]\n" R
    "      a float value to config the text size (in point) to display formulas, the default\n"
    "      is 20\n\n" B
    "  -foreground=[COLOR]\n" R
    "      config the foreground color to display formulas; the value can be a color name or\n"
    "      in the form of #AARRGGBB; default is black\n\n" B
    "  -background=[COLOR]\n" R
    "      config the background color to display formulas; the value can be a color name or\n"
    "      in the form of #AARRGGBB; default is transparent\n\n" B
    "  -padding=[VALUE]\n" R
    "      a float value to config spaces (in pixel) to add to the SVG images, "
    "the default is 10\n\n" B
    "  -maxwidth=[VALUE]\n" R
    "      config the max width of the graphics context, the default is 720 pixels; this option\n"
    "      has weak limits on the SVG images, thus the width of the SVG image may be wider than\n"
    "      the value defined by this option\n\n" B
    "BATCH MODE\n" R
    "The application will save the SVG images produced by the LaTeX codes that parsed from the\n"
    "given file (specified by the option '-samples') into the directory specified by the option\n"
    "'-outputdir'.\n\n" B
    "  -outputdir=[WHERE]\n" R
    "      indicates the directory to save the SVG images\n\n" B
    "  -samples=[FILE]\n" R
    "      specifies the file that contains various LaTeX codes split by a line that consists of\n"
    "      the character '\%' only, the default is './res/SAMPLES.tex'\n\n" B
    "  -prefix=[VALUE]\n" R
    "      specifies the prefix of the filename of the SVG images, the default is ''; for example,\n"
    "      if 2 pieces of code has given with the option '-prefix=a_', the filename of the SVG\n"
    "      images will be 'a_0.svg' and 'a_1.svg'\n\n" B
    "SINGLE MODE\n\n"
    "  -input=[CODE]\n" R
    "      the source code that is written in LaTeX\n\n" B
    "  -output=[FILE]\n" R
    "      indicates where to save the produced SVG image, only works if the option '-input' has given\n\n";
  __print("%s", msg);
  return 0;
}

int main(int argc, char* argv[]) {
  vector<string> opts;
  opts.reserve(argc);
  for (int i = 0; i < argc; i++) opts.emplace_back(argv[i]);

  if (indexOf(opts, string("-h")) >= 0) return runHelp();


  LaTeX::init();

  int result = 0;
  if (indexOf(opts, string("-headless")) >= 0) {
    result = runHeadless(opts);
  } else {
    result = runHeadless(opts);
  }

  LaTeX::release();
  return result;
}

