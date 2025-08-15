import {test, expect, Locator} from '@playwright/test';
import fs from 'fs';

test.setTimeout(120000);
test('Get all contests that have test cases published.', async ({ page }) => {
    // Load dumped data
    const dumpFile = 'dump.json';
    let data = {};
    // Access page to get new data
    await page.goto('https://www.dropbox.com/sh/nx3tnilzqz7df8a/AAAYlTq2tiEHl5hsESw6-yfLa?e=1&dl=0');
    await page.evaluate(async () => {
        const delay = ms => new Promise(resolve => setTimeout(resolve, ms));
        let len = 0;
        while (true) {
            const newLen = document.querySelectorAll('div[role="row"]').length;
            if (len === newLen)
                break;
            len = newLen;
            document.querySelectorAll('div[role="row"]')[len-1].scrollIntoView({ behavior: "smooth", block: "end", inline: "nearest" });
            await delay(10000);
        }
    });

    const body: Locator = page.locator('.dig-Table-body').first();
    const rows: Locator = body.locator('div[role="row"]');
    const cnt = await rows.count();
    for (let index= 0; index < cnt ; index++) {
        const row: Locator = rows.nth(index);
        const cell: Locator = row.locator('div[role="cell"]').first();
        const atag: Locator = cell.locator('a').first();
        const title = await cell.innerText();
        const link = await atag.getAttribute('href');
        data[title.toLowerCase()] = link;
    }
    fs.writeFileSync(dumpFile, JSON.stringify(data));
});
