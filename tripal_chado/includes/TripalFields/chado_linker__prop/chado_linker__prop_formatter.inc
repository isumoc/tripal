<?php

class chado_linker__prop_formatter extends ChadoFieldFormatter {
  // The default lable for this field.
  public static $default_label = 'Chado Property';

  // The list of field types for which this formatter is appropriate.
  public static $field_types = array('chado_linker__prop');


  /**
   *
   * @see TripalFieldFormatter::settingsForm()
   */
  public function settingsForm($view_mode, $form, &$form_state) {

  }

  /**
   *
   * @see TripalFieldFormatter::view()
   */
  public function view(&$element, $entity_type, $entity, $langcode, $items, $display) {
    $field_name = $this->field['field_name'];
    $chado_table = $this->instance['settings']['chado_table'];

    $list = array();
    foreach ($items as $index => $item) {
      $list[$index] = $item['value'];
    }

    // If more than one value has been found display all values in an unordered
    // list.
    if (count($list) > 1) {
      $content = theme_item_list(array(
        'items' => $list,
        'title' => '',
        'attributes' => array('class' => array($entity->bundle . '-properties-list', 'properties-field-list')),
        'type' => 'ul'
      ));
    }
    else {
      $content = $list[0];
    }
    $element[0] = array(
      // We create a render array to produce the desired markup,
      '#type' => 'markup',
      '#markup' => $content,
    );
  }
}
