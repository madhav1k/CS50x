import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    previous_day_cases = dict()
    new_cases = dict()
    for row in reader:
        state = str(row["state"])
        current_day_cases = int(row["cases"])
        if state not in previous_day_cases:
            previous_day_cases[state] = current_day_cases
            new_cases[state] = []
        else:
            current_day_new_cases = current_day_cases - previous_day_cases[state]
            previous_day_cases[state] = current_day_cases
            if state not in new_cases:
                new_cases[state] = []
            if len(new_cases[state]) >= 14:
                new_cases[state].pop(0)
            new_cases[state].append(current_day_new_cases)
    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        last_7days = new_cases[state][7:]
        prev_7days = new_cases[state][:7]
        last_avg = round(sum(last_7days) / 7)
        prev_avg = round(sum(prev_7days) / 7)
        if last_avg - prev_avg > 0:
            msg = "an increase"
        else:
            msg = "a decrease"
        try:
            p = round((abs(last_avg - prev_avg) / prev_avg) * 100, 2)
        except ZeroDivisionError:
            raise ZeroDivisionError
        print(f"{state} had a 7-day average of {last_avg} and {msg} of {p}%.")


main()
