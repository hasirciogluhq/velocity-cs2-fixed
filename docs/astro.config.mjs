import { defineConfig } from 'astro/config';

// GitHub Pages serves the site from /<repo>/. Override with DOCS_SITE / DOCS_BASE for another host.
export default defineConfig({
  site: process.env.DOCS_SITE ?? 'https://hasirciogluhq.github.io',
  base: process.env.DOCS_BASE ?? '/velocity-cs2-fixed',
  trailingSlash: 'always',
  markdown: {
    shikiConfig: { theme: 'css-variables' },
  },
});
