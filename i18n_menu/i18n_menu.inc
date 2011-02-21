<?php
// $Id: i18n.module,v 1.41.2.49.2.1 2010/09/14 11:30:30 jareyero Exp $
/**
 * @file
 * Internationalization (i18n) module - Translation set
 */
class i18n_menu_link_translation_set extends i18n_translation_set {
  /**
   * Load all path translations
   */
  public function load_translations() {
    $translations = array();
    $query = db_select('menu_links', 'ml');
    $query->leftJoin('menu_router', 'm', 'm.path = ml.router_path');
    $query->fields('ml');
    // Weight should be taken from {menu_links}, not {menu_router}.
    $query->addField('ml', 'weight', 'link_weight');
    $query->fields('m');
    $query->condition('ml.i18n_tsid', $this->tsid);
    while ($item = $query->execute()->fetchAssoc()) {
      $item['weight'] = $item['link_weight'];
      _menu_link_translate($item);
      $translations[$item['language']] = $item;
    }
    return $translations;
  }
}