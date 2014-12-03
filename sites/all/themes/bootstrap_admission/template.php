<?php

/**
 * @file
 * template.php
 */
/*
function bootstrap_admission_form_alter(&$form, &$form_state, $form_id) {
    if($form_id == "user_register_form") {
        $form['account']['mail']['#required'] = 0;
        $form['#validate'][] = 'bootstrap_admission_user_register_form_validate';
        $form['#submit'][] = 'bootstrap_admission_user_register_form_submit';
    }
}

function bootstrap_admission_user_register_form_validate(&$form, &$form_state) {
    $x=1;
}

function bootstrap_admission_user_register_form_submit(&$form, &$form_state) {
    $x=1;
}

 */

/**
 * Overrides theme_breadcrumb().
 *
 * Print breadcrumbs as an ordered list.
 */
function bootstrap_admission_breadcrumb($variables) {
    $output = '';
    $breadcrumb = $variables['breadcrumb'];

    // Determine if we are to display the breadcrumb.
    $bootstrap_breadcrumb = theme_get_setting('bootstrap_breadcrumb');
    if ( $bootstrap_breadcrumb == 1 || ($bootstrap_breadcrumb == 2 && arg(0) == 'admin') ) {
        
        // Make sure the Home breadcrump is always visible if there are no crumbs
        $breadcrumb[0] = empty($breadcrumb) ? array('data' => 'Home', 'class' => array('active') ) : $breadcrumb[0];
        
        $output = theme('item_list', array(
            'attributes' => array(
                'class' => array('breadcrumb'),
            ),
            'items' => $breadcrumb,
            'type' => 'ol',
        ));
    }
    return $output;
}