-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check crime_scenes_report table to get more information about the crime.
SELECT description FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36.
-- No known witnesses.

-- Check interview transcripts from interviews table as 3 interviews were conducted with witnesses on crime day.
SELECT transcript FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";

-- Transcript 1
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

-- Check for security footage of car leaving lot within 10 minutes using people & bakery_security_logs tables.
SELECT name FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit";

    -- Suspects: Vanessa, Bruce, Barry, Luca, Sofia, Iman, Diana, Kelsey

-- Transcript 2
-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- Check for names of people who withdrew money from ATM on Leggett Street on July 28, 2021 using people, bank_accounts & atm_transactions tables.
SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

    -- Suspects: Bruce, Diana, Brooke, Kenny, Iman, Luca, Taylor, Benista
    -- Common Suspects: Bruce, Luca, Iman, Diana

-- Transcript 3
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Check for people who called on July 28 for less than a minute using people & phone_calls tables.
SELECT name FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

    -- Suspects: Sofia, Kelsey, Bruce, Kelsey, Taylor, Diana, Carina, Kenny, Benista
    -- Common Suspects: Bruce, Diana

-- Check for names of passengers who took the earliest flight out of Fiftyville the next day i.e. July 29 using people, passengers, flights & airports tables.
SELECT name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id =
(
    SELECT id FROM flights
    WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id =
    (
        SELECT id FROM airports WHERE city = "Fiftyville"
    )
    ORDER BY hour, minute
    LIMIT 1
);

    -- Suspects: Doris, Sofia, Bruce, Edward, Kelsey, Taylor, Kenny, Luca
    -- The THIEF is: Bruce

-- Now to find the destination city Bruce escaped to using airports & flights tables.
SELECT city FROM airports
WHERE id =
(
    SELECT destination_airport_id FROM flights
    WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id =
    (
        SELECT id FROM airports WHERE city = "Fiftyville"
    )
    ORDER BY hour, minute
    LIMIT 1
);

    -- The city the thief ESCAPED TO: New York City

-- Finally to find Bruce's accomplice using people & phone_calls tables.
SELECT name FROM people
WHERE phone_number =
(
    SELECT receiver FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller =
    (
        SELECT phone_number FROM people WHERE name = "Bruce"
    )
);

    -- The ACCOMPLICE is: Robin
