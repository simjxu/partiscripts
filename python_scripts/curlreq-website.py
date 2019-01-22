import requests
import json
#
# # Go to inspect element, on the machine you are interested in, and choose the something like "37"
# # Use https://curl.trillworks.com/ to convert, then copy the cookies and headers
#



cookies = {
    '_ga': 'GA1.2.1232191206.1542135003',
    '_gcl_au': '1.1.1246296016.1542135004',
    'hubspotutk': '07c2268fbb252285eb85683b66c45d57',
    '__qca': 'P0-425995475-1542305671754',
    'optimizelyEndUserId': 'oeu1544646071772r0.34790860907805077',
    'mp_8d5683647b7a6ae0a4c9be0cbea1d77d_mixpanel': '%7B%22distinct_id%22%3A%20%22167a414987db3c-0ee7e33c77f653-35677407-384000-167a414987e184%22%2C%22%24device_id%22%3A%20%22167a414987db3c-0ee7e33c77f653-35677407-384000-167a414987e184%22%2C%22mp_lib%22%3A%20%22Segment%3A%20web%22%2C%22%24search_engine%22%3A%20%22google%22%2C%22%24initial_referrer%22%3A%20%22https%3A%2F%2Fwww.google.com%2F%22%2C%22%24initial_referring_domain%22%3A%20%22www.google.com%22%7D',
    '_ceg.s': 'pjnix5',
    '_ceg.u': 'pjnix5',
    '__hssrc': '1',
    'mp_170fb41bea82be678c2c3a19c8a1d92a_mixpanel': '%7B%22distinct_id%22%3A%20%22simon%40particle.io%22%2C%22%24device_id%22%3A%20%221670e68bd89aac-0ce5c9acc4a6e-1e386652-384000-1670e68bd8a959%22%2C%22mp_lib%22%3A%20%22Segment%3A%20web%22%2C%22%24initial_referrer%22%3A%20%22https%3A%2F%2Fconsole.particle.io%2Flogin%22%2C%22%24initial_referring_domain%22%3A%20%22console.particle.io%22%2C%22%24user_id%22%3A%20%22simon%40particle.io%22%2C%22mp_name_tag%22%3A%20%22simon%40particle.io%22%2C%22id%22%3A%20%22simon%40particle.io%22%2C%22%24email%22%3A%20%22simon%40particle.io%22%2C%22%24username%22%3A%20%22simon%40particle.io%22%2C%22first_name%22%3A%20%22Continental%22%2C%22last_name%22%3A%20%22Admin%22%2C%22business_account%22%3A%20true%2C%22company_name%22%3A%20%22Continental%22%2C%22firstname%22%3A%20%22Continental%22%2C%22lastname%22%3A%20%22Admin%22%2C%22isbusiness%22%3A%20true%2C%22company%22%3A%20%22Continental%22%2C%22%24first_name%22%3A%20%22Continental%22%2C%22%24last_name%22%3A%20%22Admin%22%2C%22%24name%22%3A%20%22Continental%20Admin%22%7D',
    'mfa_prompt_enroll_skip': 'true',
    'ember_simple_auth_session': '%7B%22authenticated%22%3A%7B%22authenticator%22%3A%22authenticator%3Aoauth2-n%22%2C%22token_type%22%3A%22bearer%22%2C%22access_token%22%3A%2258f4c805058309ca1f5c72aefb5036a29526d43c%22%2C%22expires_in%22%3A7776000%2C%22refresh_token%22%3A%224f8f4f93bcd9822ac162f493b63e292ebe6734cb%22%2C%22username%22%3A%22simon%40particle.io%22%2C%22domain%22%3A%22.particle.io%22%7D%7D',
    'spark-session': 'zjYm6Q3TBz91SF03pHrpFGVny',
    'mp_9c087376c4fc42081fc437d29d5d2b89_mixpanel': '%7B%22distinct_id%22%3A%20%22simon%40particle.io%22%2C%22%24device_id%22%3A%20%2216718e8c2bc958-094194958b9ef3-1e386652-384000-16718e8c2bd10f4%22%2C%22mp_lib%22%3A%20%22Segment%3A%20web%22%2C%22%24initial_referrer%22%3A%20%22%24direct%22%2C%22%24initial_referring_domain%22%3A%20%22%24direct%22%2C%22%24user_id%22%3A%20%22simon%40particle.io%22%2C%22mp_name_tag%22%3A%20%22simon%40particle.io%22%2C%22id%22%3A%20%22simon%40particle.io%22%2C%22%24email%22%3A%20%22simon%40particle.io%22%2C%22%24search_engine%22%3A%20%22google%22%7D',
    '_gid': 'GA1.2.798076865.1547480888',
    'ajs_user_id': '%22simon%40particle.io%22',
    'ajs_anonymous_id': '%227a83bb4c-c653-47ee-83e3-b2ed6ff93aa8%22',
    'ajs_group_id': 'null',
    'mp_96d23b6358add30f5b4b55fb14ed15b2_mixpanel': '%7B%22distinct_id%22%3A%20%22simon%40particle.io%22%2C%22%24device_id%22%3A%20%221671894e8c073d-00aed7220e723b-1e386652-13c680-1671894e8c1ec5%22%2C%22mp_lib%22%3A%20%22Segment%3A%20web%22%2C%22%24search_engine%22%3A%20%22google%22%2C%22%24initial_referrer%22%3A%20%22https%3A%2F%2Fwww.google.com%2F%22%2C%22%24initial_referring_domain%22%3A%20%22www.google.com%22%2C%22%24user_id%22%3A%20%22simon%40particle.io%22%2C%22mp_name_tag%22%3A%20%22simon%40particle.io%22%2C%22id%22%3A%20%22simon%40particle.io%22%2C%22%24email%22%3A%20%22simon%40particle.io%22%7D',
    'fs_uid': 'rs.fullstory.com`6F32Z`5718039073914880:5629499534213120`simon%40particle.io`',
    '_fbp': 'fb.1.1547742686689.207146437',
    '__hstc': '135831982.07c2268fbb252285eb85683b66c45d57.1542135003638.1547678766171.1547742730308.180',
}

headers = {
    'Authorization': 'Basic dXNlcl8xN2YxYTJjNjg5Y2Y3ZTNiZmFhM2UwOGRiOTk1Nzk0OGI5OTY4ZmM0ZWFmYTllYzNmNGE1OGZhZTY3OTE4YTY5OnBhc3NfZjg0ZTk4MjRjMzUxM2M2MjMxMTlmYTc1ZWIxYTNiZDcyZmE5YTdhZWZmNjFjMDMwNTAyY2MzOGUwNWE1NmU1Zg==',
    'Origin': 'https://admin.particle.io',
    'Accept-Encoding': 'gzip, deflate, br',
    'Accept-Language': 'en-US,en;q=0.9',
    'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36',
    'content-type': 'application/json',
    'accept': 'application/json',
    'Referer': 'https://admin.particle.io/',
    'Connection': 'keep-alive',
}

filetext = open("serial_num.txt")
device_ids = filetext.read().split("\n")
num_ids = len(device_ids)
for i in range(num_ids):
    request_url = 'https://admin-api.particle.io/devices?filter=%7B%22serial_number%22%3A%22' + str(device_ids[i]) + '%22%7D&range=%5B0%2C9%5D&sort=%5B%22id%22%2C%22DESC%22%5D'
    info_text = requests.get(request_url, headers=headers, cookies=cookies)
    info_text = info_text.json()
    print(device_ids[i], info_text[0]["id"])