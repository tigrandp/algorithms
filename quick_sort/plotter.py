
import glob
import matplotlib.pyplot as plt
import os


def plot_file_content(filename, dir_name):
    print (filename)
    x, y = [], []
    with open(filename) as f:
        content = f.read().split('\n')
        for line in content:
            if not line:
                break
            res = line.split(' ')
            x.append(float(res[0]))
            y.append(float(res[1]))

    label = filename.split('.')[0].split('/')[1]
    plt.plot(x, y, label=label)


def plot_run_stats(dir_name):
    plt.clf()
    files = glob.glob(dir_name + '/' + '*.txt')
    for filename in files:
        plot_file_content(filename, dir_name)

    plt.ylabel('Run time in microseconds')
    plt.xlabel('Size of sequence')
    plt.title('Runtime plt for ' + dir_name + ' input')
    plt.legend()
    plt.savefig(dir_name + '.png')


def get_directories(root):
    paths = os.walk(root)
    for _, directories, _ in paths:
        return directories


def run():
    directories = get_directories('.')
    for directory in directories:
        plot_run_stats(directory)


if __name__ == '__main__':
    run()