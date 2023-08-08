-- Let's begin by looking at the crime_scene_reports of the day in question,
-- July 28, 2021 that took place on Humphrey Street at 10:15am (per the crime_scene_reports)

SELECT * FROM crime_scene_reports
 WHERE year = "2021"
   AND month = "7"
   AND day = "28"
ORDER BY day DESC;
  -- This query lets us know that there were three witnesses present for the crime
  -- and that their interviews will mention the bakery

-- From here, let's look at interviews
SELECT * FROM interviews
 WHERE year = 2021
   AND month = 7
   AND day = 28
ORDER BY day DESC;
  -- this query provides us with the witness info of the thief:

-- id: 161 name: Ruth
  -- Within 10 mins of theft, saw them drive away from bakery parking lot

-- id: 162 name: Eugene
  -- Saw the thief withdraw money from Leggett Street ATM

-- id: 163 name: Raymond
  -- Heard the thief talk to someone for less than a minute, heard them
  -- say they were planning on taking the earliest flight out of Fiftyville tomorrow, 7/29/2021
  -- Thief asked person to buy their ticket


-- FOLLOWING LEADS
-- RUTH
-- bakery parking lot
SELECT * FROM bakery_security_logs
 WHERE year = 2021
   AND month = 7
   AND day = 28
ORDER BY hour ASC;
-- From this query we can see that 8 vehicles exited the bakery parking lot,
-- leaving us 8 suspect's license plates to run
-- Exit time - License plate
-- 10: 16 - 5P2BI95 - Vanessa
-- 10: 18 - 94KL13X - Bruce
-- 10: 18 - 6P58WS2 - Barry
-- 10: 19 - 4328GD8 - Luca
-- 10: 20 - G412CB7 - Sofia
-- 10: 21 - L93JTIZ - Iman
-- 10: 23 - 322W7JE - Diana
-- 10: 23 - 0NTHK55 - Kelsey


-- Now, let's generate names for the license plates:
  SELECT license_plate, name FROM people
ORDER BY license_plate ASC;
-- 5P2BI95 - Vanessa
-- 94KL13X - Bruce
-- 6P58WS2 - Barry
-- 4328GD8 - Luca
-- G412CB7 - Sofia
-- L93JTIZ - Iman
-- 322W7JE - Diana
-- 0NTHK55 - Kelsey
-- These were the names that corresponded to the license_plates
-- of the vehicles that were seen leaving the bakery
-- within the timeframe Ruth described.

-- EUGENE
-- ATM_transactions from Leggett Street
SELECT * FROM atm_transactions
 WHERE atm_location = "Leggett Street"
   AND year = 2021
   AND month = 7
   AND day = 28
ORDER BY day ASC;
-- This provides us with 8 account numbers that withdrew money from
-- the Leggett Street ATM
-- id  |  account_number
-- 246 |  28500762
-- 264 |  28296815
-- 266 |  76054385
-- 267 |  49610011
-- 269 |  16153065
-- 275 |  86363979
-- 288 |  25506511
-- 313 |  81061156
-- 336 |  26013199

-- Let's assign names to these account_numbers, they will let us see
-- if there are corresponding names and license_plate numbers
  SELECT name, account_number FROM people
    JOIN bank_accounts
      ON people.id = bank_accounts.person_id
ORDER BY account_number ASC

  -- This allows us to put names to the account numbers we received from our
  -- previous query involving atm transactions
-- id  |  account_number | name
-- 246 |  28500762       | Luca
-- 264 |  28296815       | Kenny
-- 266 |  76054385       | Taylor
-- 267 |  49610011       | Bruce
-- 269 |  16153065       | Brooke
-- 275 |  86363979       | Kaelyn
-- 288 |  25506511       | Iman
-- 313 |  81061156       | Benista
-- 336 |  26013199       | Diana

-- After comparing the people who withdrew from the ATM
-- with those who were leaving the parking garage the
-- day of the theft, we're left with 4 suspects:
--
-- Current list of suspects:
-- Luca, Bruce, Iman, Diana

-- RAYMOND
-- Let's see if we can further narrow down the suspect pool after using the
-- information Raymond provided us
-- The thief is taking the earliest flight out of Fiftyville on 7/29/2021
  SELECT * FROM flights
   WHERE year = 2021
    AND month = 7
    AND day = 29
  ORDER BY hour ASC;
  -- From this query, we can see that the earliest flight on 7/29/2021 had
  -- an id of 36, and destination_airport_id of 4 and departed at 8:20am

-- With this information we can determine where the thief was headed
  SELECT * from airports 
ORDER BY id ASC;
  -- From this query, we can determine that the airport id of 4 is
  -- LaGuardia Airport in New York City

-- Let's try to see who was on that flight
  SELECT * FROM people
    JOIN passengers ON passengers.passport_number = people.passport_number
   WHERE flight_id = 36
ORDER BY name ASC;
-- from this query, we can see a few of the suspects were on the flight to NYC:
-- Bruce and Luca
-- However, it also shows that some of the other people who left the bakery within
-- the 10 min window were also going to NYC:
-- Sofia, Kelsey

-- This at least narrows down the main suspect as Bruce


-- With this information, let's see if Bruce called anyone the morning of the theft
-- as this should be his accomplice
-- Bruce's phone_number:
-- (367) 555-5533

   SELECT * FROM phone_calls
    WHERE caller = (367) 555-5533;
  -- This query allows us to see all of Bruce's calls
  -- Focusing on the day of the crime, 7/28 and looking for any that didn't last a minute long
  -- we can see he only had one call the day of the crime that was shorter than a minute
  -- to which he called (375) 555-8161, this must be his accomplice

  SELECT name, phone_number
    FROM people
   WHERE phone_number = "(375) 555-8161";
-- Given that the number belongs to a Robin, they must be Bruce's accomplice to the crime


Answers:
-- New York City
-- Main suspect: Bruce
-- Accomplice: Robin
