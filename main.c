#include <math.h>
#include <stdio.h>
#include <ctype.h>

///
/// \author Basic graph constructor V1.0.0 by Yeloki
/// \arg zoom
/// \arg height
/// \arg x-start
/// \fun f - function

double f(double x) {
  return cos(x);
}

int g_zoom = 8; // step (1 step = 1 / zoom)
double g_x_start = -50.0 / 8; // start of coord system
int g_height = 41; // can be modified
int g_width = 101; // std graph size (not modified)

int common_comparator(const char a[], const char b[]) {
  int i = 0;
  while (1) {
    if (a[i] != b[i])
      return 0;
    if (a[i] == 0 && b[i] == 0)
      return 1;
    ++i;
  }
}

int parce(const char arg[]) {
  size_t i = 0;
  char key[10] = "";
  while (arg[i] != '=') {
    if (arg[i] == 0)
      return 0;
    key[i] = arg[i];
    ++i;
  }

  if (common_comparator(key, "zoom")) {
    int value = 0;
    ++i;
    while (arg[i] != 0) {
      if (isdigit(arg[i]))
        value = value * 10 + (arg[i] - '0');
      else
        return 0;
      ++i;
    }
    g_zoom = value;
  } else if (common_comparator(key, "height")) {
    int value = 0;
    ++i;
    while (arg[i] != 0) {
      if (isdigit(arg[i]))
        value = value * 10 + (arg[i] - '0');
      else
        return 0;
      ++i;
    }
    g_height = value;
  } else if (common_comparator(key, "x-start")) {
    double value = 0;
    ++i;
    int f = 1, k = 1, n = 1;
    if (arg[i] == '-')
      n = -1, ++i;
    while (arg[i] != 0) {
      if (isdigit(arg[i]))
        if (f)
          value = value * 10 + (arg[i] - '0');
        else
          value += (double) (arg[i] - '0') / (k *= 10);
      else if (arg[i] == '.')
        f = 0;
      else
        return 0;
      ++i;
    }
    g_x_start = value * n;
  } else
    return 0;
  return 1;
}

int main(int argc, char *argv[]) {
  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      int status = parce(argv[i]);
      if (!status) {
        printf("Some error while parsing args occurred\nstop\n");
        return -1;
      }
    }
  }

  double keys[g_width];
  int vals[g_width];
  keys[0] = g_x_start;

  for (int i = 1; i < g_width; ++i) {
    keys[i] = keys[i - 1] + 1.0 / g_zoom;
  }

  for (int i = 0; i < g_width; ++i)
    vals[i] = lround(f(keys[i]) * g_zoom);
  for (int i = 0; i < g_width; ++i)
    printf((i == (g_width - 1) / 2) ? "^" : " ");
  printf("\n");

  for (int i = 0; i < g_height; ++i) {
    for (int j = 0; j < g_width; ++j) {
      if (vals[j] != (g_height - 1) / 2 - i) {
        if (i == (g_height - 1) / 2)
          printf("-");
        else if (j == (g_width - 1) / 2)
          printf("|");
        else
          printf(" ");
      } else {
        printf("*");
      }
    }
    printf((i == (g_height - 1) / 2) ? ">\n" : "\n");
  }

}
