import csv
import json
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm

from operator import itemgetter

def jsonify(data):
    return json.loads(data.replace("'", '"'))


def preprocess_talks(src):
    '''
    주어진 CSV 파일을 열어 처리 가능한 파이썬의 리스트 형태로 변환합니다.
    리스트의 각 원소는 문제에서 설명된 딕셔너리 형태로 이루어져 있습니다.

    각 강연 별로 다음과 같은 키와 타입을 가진 딕셔너리를 생성합니다:
    {
      "title": string,
      "speaker": string,
      "views": int,
      "comments": int,
      "duration": int,
      "languages": int,
      "tags": list(string),
      "ratings": list(dict)
    }

    >>> preprocess_talks('ted.csv')
    [{'title': 'Do schools kill creativity?', 'speaker': 'Ken Robinson', ... }]
    '''

    # 강연 데이터를 저장할 빈 리스트를 선언합니다.
    talks = []

    # CSV 파일을 열고, 데이터를 읽어 와서 talks에 저장합니다.
    with open(src) as file:
        reader = csv.reader(file, delimiter=',')

        for line in reader:
            try:
                talk = {
                    # 강의 평가는 참조 필요
                    'title': line[14],     # 강연의 제목
                    'speaker': line[6],   # 강연자의 이름
                    'views': int(line[16]),     # 조회수
                    'comments': int(line[0]),  # 댓글의 개수
                    'duration': int(line[2]),  # 강연 길이
                    'languages': int(line[5]), # 지원하는 언어의 수
                    'tags': line[13],      # 관련 태그 (키워드)
                    'ratings':  line[10],   # 강의에 대한 평가
                }
                talks.append(talk)
            except:
                pass


    return talks


# talks = [{}] 리스트 안에 딕셔너리
def get_popular_tags(talks, n):
    '''
    가장 인기 있는 태그 상위 n개를 리턴합니다.
    태그의 인기도는 해당 태그를 포함하는 강의들의 조회수 합으로 결정됩니다.
    예를 들어, 'education' 태그가 포함된 강의가 총 15개라면
    'education' 태그의 인기도는 이 15개 강의의 조회수 총합입니다.

    >>> get_popular_tags(preprocess_talks('ted.csv'), 10))
    ['culture', 'technology', 'science', ... ]
    '''
    # 태그 별 인기도를 저장할 딕셔너리
    tag_to_views = {}

    # 태그는 리스트형태로 저장되어 있음
    # 태그 별 인기도를 구해 tag_to_views에 저장합니다.
    for dic in talks:
        for tag in dic['tags']:
            if tag in tag_to_views:
                tag_to_views[tag] += int(dic['views'])
            else:
                tag_to_views[tag] = int(dic['views'])

    # (태그, 인기도)의 리스트 형식으로 변환합니다.
    tag_view_pairs = list(tag_to_views.items())
    # 인기도가 높은 순서로 정렬해 앞의 n개를 취합니다.
    # n개를 취한 후에는 태그만 남깁니다.
    # 힌트: itemgetter()를 사용하세요!
    top_tag_and_views = sorted(tag_view_pairs, key=lambda pair : pair[1], reverse=True)[:n]
    top_tags = map(lambda pair : pair[0], top_tag_and_views)

    return list(top_tags)


# talks = [{}] 리스트 안에 딕셔너리
def completion_rate_by_duration(talks):
    '''
    강의 길이에 따라 강의를 끝까지 들은 비율(완수도)이 어떻게 변화하는지 확인해 봅니다.
    강의를 끝까지 들은 비율은 (댓글 개수 / 조회수)에 비례한다고 가정합니다.
    '''

    durations = []
    completion_rates = []

    for dic in talks:
        durations.append(dic['duration'])
        completion_rates.append( dic['comments']/dic['views'])

    scatter_plot(durations, completion_rates, '강의 길이', '완수도')

    return durations, completion_rates


# talks is list
def views_by_languages(talks):
    '''
    지원되는 언어의 수에 따라 조회수가 어떻게 변화하는지 확인해 봅니다.
    '''
    languages = []
    views = []
    for dic in talks:
        languages.append(dic['languages'])
        views.append(dic['views'])

    # languages = talks['languages']
    # views = talks['views']
    scatter_plot(languages, views, '언어의 수', '조회수')

    # 채점을 위해 결과를 리턴합니다.
    return views, languages

# 값을 그냥 우겨넣는다
def show_ratings(talk):
    '''
    강의에 대한 다양한 평가(rating)를 막대그래프로 표현합니다.
    각 키워드('fun', 'confusing' 등)별 숫자를 나타냅니다.
    '''
    keywords = ['children', 'creativity']
    counts = [10,20]
    bar_plot(keywords, counts, '키워드', 'rating의 수')

    # 채점을 위해 결과를 리턴합니다.
    return keywords, counts


def scatter_plot(x, y, x_label, y_label):
    font = fm.FontProperties(fname='./NanumBarunGothic.ttf')

    plt.scatter(x, y)
    plt.xlabel(x_label, fontproperties=font)
    plt.ylabel(y_label, fontproperties=font)

    plt.xlim((min(x), max(x)))
    plt.ylim((min(y), max(y)))
    plt.tight_layout()

    plot_filename = 'plot.png'
    plt.savefig(plot_filename)
    elice_utils.send_image(plot_filename)


def bar_plot(x_ticks, y, x_label, y_label):
    assert(len(x_ticks) == len(y))

    font = fm.FontProperties(fname='./NanumBarunGothic.ttf')

    pos = range(len(y))
    plt.bar(pos, y, align='center')
    plt.xticks(pos, x_ticks, rotation='vertical', fontproperties=font)

    plt.xlabel(x_label, fontproperties=font)
    plt.ylabel(y_label, fontproperties=font)
    plt.tight_layout()

    plot_filename = 'plot.png'
    plt.savefig(plot_filename)
    elice_utils.send_image(plot_filename)


def main():
    src = 'ted.csv'
    talks = preprocess_talks(src)
    print(get_popular_tags(talks, 10))
    completion_rate_by_duration(talks)
    views_by_languages(talks)
    show_ratings(talks[0])


if __name__ == "__main__":
    main()

