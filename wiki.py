import requests

def get_wiki():
    query = str(input("Enter the title of wiki: "))
    # Make a request to the Wikipedia API
    response = requests.get('https://en.wikipedia.org/w/api.php', params={
        'action': 'query',
        'format': 'json',
        'titles': f'{query}',
        'prop': 'extracts',
        'exintro': '',
        'explaintext': '',
        'formatversion': 2
    })

    # Check the status code of the response
    if response.status_code == 200:
        # Load the response data into a Python dictionary
        data = response.json()
        # print(data)
        extract = data['query']['pages'][0]['extract']
        print(extract)
    else:
        print('Request failed with status code', response.status_code)